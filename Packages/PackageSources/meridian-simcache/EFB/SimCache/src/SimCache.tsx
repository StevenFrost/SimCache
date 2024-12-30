import {
  App,
  AppBootMode,
  AppInstallProps,
  AppSuspendMode,
  AppView,
  AppViewProps,
  Efb,
  RequiredProps,
  TVNode,
} from "@efb/efb-api";
import { FSComponent, VNode } from "@microsoft/msfs-sdk";

import "./SimCache.scss";

declare const BASE_URL: string;

class SimCacheView extends AppView<RequiredProps<AppViewProps, "bus">> {
  public onOpen(): void {}

  public onClose(): void {}

  public onResume(): void {}

  public onPause(): void {}

  public render(): VNode {
    return <div class="simcache-app">{super.render()}</div>;
  }
}

class SimCache extends App {
  public BootMode = AppBootMode.COLD;
  public SuspendMode = AppSuspendMode.SLEEP;

  public get name(): string {
    return "SimCache";
  }

  public get icon(): string {
    return `${BASE_URL}/Assets/app-icon.svg`;
  }

  public async install(_props: AppInstallProps): Promise<void> {
    Efb.loadCss(`${BASE_URL}/SimCache.css`);
    return Promise.resolve();
  }

  public render(): TVNode<SimCacheView> {
    return <SimCacheView bus={this.bus} />;
  }
}

Efb.use(SimCache);
