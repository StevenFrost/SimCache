import { Button, IconElement, TT, GamepadUiView, RequiredProps, TVNode, UiViewProps } from "@efb/efb-api";
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
        <div class="efb-body scroll-container">
          <div class="content">
            <header>
              <nav>
                <Button
                  class="back-button"
                  callback={(): void => {
                    this.props.appViewService.goBack();
                  }}
                >
                  <IconElement url="coui://html_ui/efb_ui/efb_apps/PilotBookApp/Assets/icons/Arrow.svg" />
                  <TT key="@fs-base-efb,TT:EFB.COMMON.BACK" format="uppercase" />
                </Button>
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
