import { TTButton, TVNode } from "@efb/efb-api";
import { FSComponent, MappedSubscribable, Subscribable, DisplayComponent } from "@microsoft/msfs-sdk";
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
  private cache_date_placed: MappedSubscribable<string>;
  private cache_date_collected: MappedSubscribable<string>;
  private cache_difficulty: MappedSubscribable<number>;
  private cache_title: MappedSubscribable<string>;
  private cache_description: MappedSubscribable<string>;
  private cache_hint: MappedSubscribable<string>;

  private readonly detailsRef = FSComponent.createRef<HTMLDetailsElement>();

  constructor(args: any) {
    super(args);

    this.currentCache = this.props.dataContext.currentDetailsId.map(cacheId => {
      this.closeHint();
      return this.props.dataContext.caches.getValue(cacheId) || Utils.makeObservableObject(this.props.dataContext.NULL_CACHE_DATA);
    });

    this.cache_id = this.currentCache.map(x => x.id.get());
    this.cache_author = this.currentCache.map(x => x.author.get());
    this.cache_date_placed = this.currentCache.map(x => this.getLocaleDateString(x.date_placed.get()));
    this.cache_date_collected = this.currentCache.map(x => this.getLocaleDateString(x.date_collected.get()));
    this.cache_difficulty = this.currentCache.map(x => x.difficulty.get());
    this.cache_title = this.currentCache.map(x => x.title.get());
    this.cache_description = this.currentCache.map(x => x.description.get());
    this.cache_hint = this.currentCache.map(x => x.hint.get());
  }

  public closeHint() {
    if (this.detailsRef.getOrDefault()) {
      this.detailsRef.instance.removeAttribute("open");
    }
  }

  private getLocaleDateString(date: Date | undefined): string {
    if (!date) {
      return "";
    }
    return date.toLocaleDateString();
  }

  public render(): TVNode<HTMLDivElement> {
    return (
      <div class="cache-details">
        <main>
          <section>
            <table>
              <caption><h1>{this.cache_title}</h1></caption>
              {/* <tr>
                <td>ID</td>
                <td>{this.cache_id}</td>
              </tr> */}
              <tr>
                <td>Author</td>
                <td>{this.cache_author}</td>
              </tr>
              <tr>
                <td>Difficulty</td>
                <td>{this.cache_difficulty}</td>
              </tr>
              <tr>
                <td>Date Hidden</td>
                <td>{this.cache_date_placed}</td>
              </tr>
              <tr>
                <td>Date Collected</td>
                <td>{this.cache_date_collected}</td>
              </tr>
            </table>
          </section>
          <section>
            <h2>Cache Description</h2>
            <p>{this.cache_description}</p>
            <p>
              <details ref={this.detailsRef}>
                <summary>Cache Hint</summary>
                <p>{this.cache_hint}</p>
              </details>
            </p>
          </section>
          <section>
            <h2>Begin Your Search</h2>
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
