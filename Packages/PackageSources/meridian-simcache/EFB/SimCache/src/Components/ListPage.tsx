import { TTButton, GamepadUiView, RequiredProps, TVNode, UiViewProps } from "@efb/efb-api";
import { FSComponent, Subscribable, VNode, SubscribableArrayEventType } from "@microsoft/msfs-sdk";
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
    const newListItem = document.createElement("li");
    this.listRef.instance.insertAdjacentElement("beforeend", newListItem);
    FSComponent.render(<CacheListItem appViewService={this.props.appViewService} itemContext={item} dataContext={this.props.dataContext} />, newListItem);
  }

  addItems(items: readonly CacheData[] | undefined): void {
    if (!items) {
      return;
    }
    for (const item of items) {
      this.addItem(item);
    }
  }

  onAfterRender(node: VNode): void {
    super.onAfterRender(node);
    this.props.dataContext.caches.sub((index: number, type: SubscribableArrayEventType, item: CacheData | readonly CacheData[] | undefined, array: readonly CacheData[]) => {
      // TODO: handle SubscribableArrayEventType.Removed (also see if updates are different than adding?)
      switch (type) {
        case SubscribableArrayEventType.Added:
          Array.isArray(item) ? this.addItems(item) : this.addItem(item!);
          break;
        case SubscribableArrayEventType.Removed:
          break;
        case SubscribableArrayEventType.Cleared:
          this.listRef.instance.innerHTML = "";
          break;
      }
    });
  }

  public render(): TVNode<HTMLDivElement> {
    return (
      <div ref={this.gamepadUiViewRef} class="simcache-page">
        <div class="efb-header"></div>
        <div class="efb-body">
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
