import { TTButton, TVNode } from "@efb/efb-api";
import { FSComponent, MappedSubscribable, Subscribable, Subject, DisplayComponent } from "@microsoft/msfs-sdk";
import { SimCacheDataManager, CacheData } from "../utils/SimCacheDataManager";
import { Utils } from "../utils/SimCacheUtils";
import "./CacheDetails.scss";

interface CacheDetailsProps {
  dataContext: SimCacheDataManager;
}

export class CacheDetails extends DisplayComponent<CacheDetailsProps> {
  public currentCache: MappedSubscribable<CacheData>;

  private cache_id: MappedSubscribable<string>;
  private cache_author: MappedSubscribable<string>;
  private cache_date_placed: MappedSubscribable<Date>;
  private cache_date_collected: MappedSubscribable<Date>;
  private cache_difficulty: MappedSubscribable<number>;
  private cache_title: MappedSubscribable<string>;
  private cache_description: MappedSubscribable<string>;
  private cache_hint: MappedSubscribable<string>;

  constructor(args: any) {
    super(args);

    this.currentCache = this.props.dataContext.currentDetailsId.map(cacheId => {
      const idx = this.props.dataContext.caches.getArray().findIndex(x => x.id.get() === cacheId);
      return idx === -1 ? Utils.makeObservableObject(this.props.dataContext.NULL_CACHE_DATA) : this.props.dataContext.caches.get(idx);
    });

    this.cache_id = this.currentCache.map(x => x.id.get());
    this.cache_author = this.currentCache.map(x => x.author.get());
    this.cache_date_placed = this.currentCache.map(x => x.date_placed.get());
    this.cache_date_collected = this.currentCache.map(x => x.date_collected.get());
    this.cache_difficulty = this.currentCache.map(x => x.difficulty.get());
    this.cache_title = this.currentCache.map(x => x.title.get());
    this.cache_description = this.currentCache.map(x => x.description.get());
    this.cache_hint = this.currentCache.map(x => x.hint.get());

  }

  private get cache() {
    return this.currentCache.get();
  }

  public render(): TVNode<HTMLDivElement> {
    return (
      <div class="cache-details">
        <header>
          <h2>{this.cache_title}</h2>
          {/* <p>dataContext.currentDetailsId: {this.props.dataContext.currentDetailsId}</p> */}
        </header>
        <main>
          <section>
            <h3>Cache Metadata</h3>
            {/* <p>ID: {this.cache_id}</p> */}
            <p>Author: {this.cache_author}</p>
            <p>Difficulty: {this.cache_difficulty}</p>
            <p>Date Hidden: {this.cache_date_placed}</p>
            <p>Date Collected: {this.cache_date_collected}</p>
          </section>
          <section>
            <h3>Cache Description</h3>
            <p>{this.cache_description}</p>
          </section>
          <section>
            <details>
              <summary><h3>Cache Hint</h3></summary>
              <p>{this.cache_hint}</p>
            </details>
          </section>
          <section>
            <h3>Begin Your Search</h3>
            <TTButton
              key="Track This Cache!"
              callback={(): void => {
                this.props.dataContext.setCurrentTrackedCache(this.cache_id.get());
              }}
            />
          </section>
        </main>
      </div>
    );
  }
}
