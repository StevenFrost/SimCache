import { ArraySubject, Subject } from "@microsoft/msfs-sdk";
import { Utils } from "./SimCacheUtils";

export interface CacheData {
  id: Subject<string>;
  author: Subject<string>;
  date_placed: Subject<Date>;
  date_collected: Subject<Date>;
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

  public caches: ArraySubject<CacheData>;
  public currentDetailsId: Subject<string>;

  constructor() {
    this.NULL_CACHE_DATA = this.getCacheData(null);
    this.isInitialized = this.initialize();
    this.caches = ArraySubject.create<CacheData>();
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

      // NOTE: `UICacheFoundEvent` is sent from the tracker view model (the UI event dispatcher is the same); we use this to re-request available caches
      // (since the date collected data stored within will have changed)
      // actually doesn't the front end view model pick this up on the internal dispatcher?  do we need this at all?
      this.CommBusListener.on("SimCache.UICacheFoundEvent", this.onCacheFoundEvent.bind(this));
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

  public placeholderSetCurrentTrackedCache(): void {
    if (this.cacheList) {
      this.setCurrentTrackedCache(this.cacheList.cache_definitions[0].meta.id);
    } else {
      console.log("placeholderSetCurrentTrackedCache called with no cache list");
    }
  }

  private getCacheData(cacheDefinition: any): any {
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
    return {
      "id": cacheDefinition.meta.id,
      "author": authorNames.join(", "),
      "date_placed": cacheDefinition.meta.date_placed,
      "date_collected": cacheDefinition.meta.date_collected,
      "difficulty": cacheDefinition.meta.difficulty,
      "title": cacheDefinition.loc_text.text.title,
      "description": cacheDefinition.loc_text.text.description,
      "hint": cacheDefinition.loc_text.text.hint
    };
  }

  private addOrUpdateCacheData(cacheDefinition: any): void {
    const cache = this.getCacheData(cacheDefinition);
    const idx = this.caches.getArray().findIndex(x => x.id.get() === cache.id);
    if (idx === -1) {
      this.caches.insert(Utils.makeObservableObject(cache) as unknown as CacheData);
    } else {
      let cacheRef: {[index: string]:any} = this.caches.get(idx);
      for (const [key, value] of Object.entries(cache)) {
        cacheRef[key].set(value);
      }
    }
  }

  private onCacheListChangedEvent(eventData: any): void {
    this.cacheList = JSON.parse(eventData);
    console.log("new cache list arrived");
    for (const cache_definition of this.cacheList.cache_definitions) {
      this.addOrUpdateCacheData(cache_definition);
    }
  }

  private onTrackedCacheChangedEvent(eventData: any): void {
    this.currentTrackedCache = JSON.parse(eventData);
    console.log(`new tracked cache: ${ this.currentTrackedCache.id }`);
    // TODO: set Subject or whatever and get UI to reflect state?
  }

  private onCacheFoundEvent(eventData: any): void {
    const data = JSON.parse(eventData);
    console.log("cache found");
    // I can probably get rid of this?  pretty sure I send a new `UICacheListChangedEvent` when the cache is found anyways
  }
}