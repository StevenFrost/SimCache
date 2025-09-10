import { MapSubject, Subject } from "@microsoft/msfs-sdk";
import { Utils } from "./SimCacheUtils";

export interface CacheData {
  id: Subject<string>;
  author: Subject<string>;
  date_placed: Subject<Date|undefined>;
  date_collected: Subject<Date|undefined>;
  difficulty: Subject<number>;
  title: Subject<string>;
  description: Subject<string>;
  hint: Subject<string>;
}

export class SimCacheDataManager {
  private CommBusListener!: CommBusListener;
  private isInitialized: Promise<void>;
  private cacheList?: any;
  private currentTrackedCache?: any;

  public readonly NULL_CACHE_DATA: CacheData;

  public caches: MapSubject<string, CacheData>;
  public currentDetailsId: Subject<string>;

  constructor() {
    this.NULL_CACHE_DATA = this.flattenCacheDefinition(null);
    this.isInitialized = this.initialize();
    this.caches = MapSubject.create<string, CacheData>();
    this.currentDetailsId = Subject.create<string>("");
  }

  private initialize(): Promise<void> {
    return new Promise(async (resolve, reject) => {
      const commBusJsLoaded = await Utils.loadJsNoExcept("/JS/Services/CommBus.js");
      if (!commBusJsLoaded) {
        const message = "Unable to load CommBus.js.";
        console.error(message);
        reject(message);
      }
      this.CommBusListener = await Utils.registerCommBusListenerAsync();
      this.CommBusListener.on("SimCache.UICacheListChangedEvent", this.onCacheListChangedEvent.bind(this));
      this.CommBusListener.on("SimCache.UITrackedCacheChangedEvent", this.onTrackedCacheChangedEvent.bind(this));
      resolve();
    });
  }

  public async requestAvailableCaches(): Promise<void> {
    await this.isInitialized;
    // TODO: get actual locale
    const data = {
      locale: "en-US"
    };
    this.CommBusListener.callWasm("SimCache.UIRequestAvailableCachesEvent", JSON.stringify(data));
  }

  public setCurrentTrackedCache(cacheId: string): void {
    const data = {
      id: cacheId
    };
    this.CommBusListener.callWasm("SimCache.UICacheSelectedEvent", JSON.stringify(data));
  }

  private flattenCacheDefinition(cacheDefinition: any): any {
    if (!cacheDefinition) {
      return {
      "id": "",
      "author": "No Data",
      "date_placed": new Date(),
      "date_collected": new Date(),
      "difficulty": 0,
      "title": "No Data",
      "description": "No Data",
      "hint": "No Data"
      }
    }
    const authorNames = cacheDefinition.meta.authors.map((id: string) => this.cacheList.authors.find((author: any) => author.id === id).name);
    const parseDate = (cacheDate: string|boolean) => cacheDate === false ? undefined : new Date(cacheDate as string);
    return {
      "id": cacheDefinition.meta.id,
      "author": authorNames.join(", "),
      "date_placed": parseDate(cacheDefinition.meta.date_placed),
      "date_collected": parseDate(cacheDefinition.meta.date_collected),
      "difficulty": cacheDefinition.meta.difficulty,
      "title": cacheDefinition.loc_text.text.title,
      "description": cacheDefinition.loc_text.text.description,
      "hint": cacheDefinition.loc_text.text.hint
    };
  }

  private addOrUpdateCacheData(cacheDefinition: any): void {
    const cache = this.flattenCacheDefinition(cacheDefinition);
    const existingCacheData: {[index: string]:any}|undefined = this.caches.getValue(cache.id);
    if (existingCacheData) {
      for (const [key, value] of Object.entries(cache)) {
        existingCacheData[key].set(value);
      }
    } else {
      this.caches.setValue(cache.id, Utils.makeObservableObject(cache) as unknown as CacheData);
    }
    // TODO: if we ever remove a cache at runtime, clear out stale caches from `this.caches`
  }

  private onCacheListChangedEvent(eventData: any): void {
    this.cacheList = JSON.parse(eventData);
    for (const cache_definition of this.cacheList.cache_definitions) {
      this.addOrUpdateCacheData(cache_definition);
    }
  }

  private onTrackedCacheChangedEvent(eventData: any): void {
    this.currentTrackedCache = JSON.parse(eventData);
    // TODO: invoke tracker ingamepanel if requested
  }
}