import { RequiredProps, TVNode, UiViewProps } from "@efb/efb-api";
import { FSComponent, MappedSubscribable, Subscribable, DisplayComponent, VNode } from "@microsoft/msfs-sdk";
import { SimCacheDataManager, CacheData } from "../utils/SimCacheDataManager";
import { StarRating } from "./StarRating";
import "./CacheListItem.scss";

interface CacheListItemProps extends RequiredProps<UiViewProps, "appViewService"> {
  itemContext: CacheData;
  dataContext: SimCacheDataManager;
}

export class CacheListItem extends DisplayComponent<CacheListItemProps> {
  private readonly linkRef = FSComponent.createRef<HTMLAnchorElement>();
  private collected_glyph: MappedSubscribable<string>;

  constructor(args: any) {
    super(args);
    this.collected_glyph = this.props.itemContext.date_collected.map(x => x ? "&#10004;" : "");
  }

  onAfterRender(node: VNode): void {
    this.linkRef.instance.addEventListener("click", (e) => {
      e.preventDefault();
      this.props.dataContext.currentDetailsId.set(this.props.itemContext.id.get());
      this.props.appViewService.open("DetailsPage");
    });
  }

  public render(): TVNode<HTMLLIElement> {
    return (
      <li class="card-list-item">
        <div class="card-grid-container">
          <h2><a href="#" ref={this.linkRef}>{this.props.itemContext.title}</a></h2>
          <div role="meter"><StarRating rating={this.props.itemContext.difficulty} /></div>
          <div class="container-check">{this.collected_glyph}</div>
        </div>
      </li>
    );
  }
}
