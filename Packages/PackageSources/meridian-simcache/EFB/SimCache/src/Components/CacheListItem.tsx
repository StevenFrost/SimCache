import { TTButton, RequiredProps, TVNode, UiViewProps } from "@efb/efb-api";
import { FSComponent, Subscribable, DisplayComponent } from "@microsoft/msfs-sdk";
import { SimCacheDataManager, CacheData } from "../utils/SimCacheDataManager";
import "./CacheListItem.scss";

interface CacheListItemProps extends RequiredProps<UiViewProps, "appViewService"> {
  itemContext: CacheData;
  dataContext: SimCacheDataManager;
}

export class CacheListItem extends DisplayComponent<CacheListItemProps> {
  public render(): TVNode<HTMLLIElement> {
    return (
      <li class="card-list-item">
        <h2>{this.props.itemContext.title}</h2>
        <p>Difficulty: {this.props.itemContext.difficulty}</p>
        <p>Collected: {this.props.itemContext.date_collected}</p>
        <TTButton
          key="View Cache Details"
          callback={(): void => {
            this.props.dataContext.currentDetailsId.set(this.props.itemContext.id.get());
            this.props.appViewService.open("DetailsPage");
            }}
        />
      </li>
    );
  }
}
