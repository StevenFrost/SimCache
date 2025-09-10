import { GamepadUiView, RequiredProps, TVNode, UiViewProps } from "@efb/efb-api";
import { FSComponent, Subscribable, VNode, SubscribableMapEventType } from "@microsoft/msfs-sdk";
import { SimCacheDataManager, CacheData } from "../utils/SimCacheDataManager";
import { CacheListItem } from "./CacheListItem";
import "../Common.scss";
import "./ListPage.scss";

interface ListPageProps extends RequiredProps<UiViewProps, "appViewService"> {
  dataContext: SimCacheDataManager;
}

export class ListPage extends GamepadUiView<HTMLDivElement, ListPageProps> {
  public readonly tabName = ListPage.name;
  private readonly listRef = FSComponent.createRef<HTMLUListElement>();

  addItem(item: CacheData): void {
    FSComponent.render(<CacheListItem appViewService={this.props.appViewService} itemContext={item} dataContext={this.props.dataContext} />, this.listRef.instance);
  }

  onAfterRender(node: VNode): void {
    super.onAfterRender(node);
    this.props.dataContext.caches.sub((map: ReadonlyMap<string, CacheData>, type: SubscribableMapEventType, key: string, value: CacheData) => {
      switch (type) {
        case SubscribableMapEventType.Added:
          this.addItem(value);
          break;
        case SubscribableMapEventType.Changed:
        case SubscribableMapEventType.Deleted:
          // TODO: handle these cases if we ever modify or remove entries in `this.props.dataContext.caches`
          console.error(`SimCache ListPage: SubscribableMapEventType ${type} not supported`);
          break;
      }
    });
  }

  public render(): TVNode<HTMLDivElement> {
    return (
      <div ref={this.gamepadUiViewRef} class="simcache-page">
        <div class="efb-header"></div>
        <div class="efb-body scroll-container">
          <div class="content">
            <header>
              <h1>Welcome to SimCache</h1>
            </header>
            <main>
              <ul class="card-container" ref={this.listRef}></ul>
            </main>
          </div>
        </div>
      </div>
    );
  }
}
