import { TTButton, GamepadUiView, RequiredProps, TVNode, UiViewProps } from "@efb/efb-api";
import { FSComponent, Subscribable } from "@microsoft/msfs-sdk";
import { CacheDetails } from "./CacheDetails";
import { SimCacheDataManager } from "../utils/SimCacheDataManager";
import "../Common.scss";
import "./DetailsPage.scss";

interface DetailsPageProps extends RequiredProps<UiViewProps, "appViewService"> {
  dataContext: SimCacheDataManager;
}

export class DetailsPage extends GamepadUiView<HTMLDivElement, DetailsPageProps> {
  public readonly tabName = DetailsPage.name;

  public render(): TVNode<HTMLDivElement> {
    return (
      <div ref={this.gamepadUiViewRef} class="simcache-page">
        <div class="efb-header"></div>
        <div class="efb-body">
          <div class="content">
            <header>
              <h1>Cache Details</h1>
              <nav>
                <TTButton
                  key="Go back"
                  type="secondary"
                  callback={(): void => {
                    this.props.appViewService.goBack();
                  }}
                />
              </nav>
            </header>
            <main>
              <CacheDetails
                dataContext={this.props.dataContext}
              />
            </main>
          </div>
        </div>
      </div>
    );
  }
}
