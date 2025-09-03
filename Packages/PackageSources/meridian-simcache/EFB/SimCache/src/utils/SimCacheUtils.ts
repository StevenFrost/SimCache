import { ObjectUtils, Subject } from "@microsoft/msfs-sdk";
import { Efb } from "@efb/efb-api";

export class Utils {

  public static async loadJsNoExcept(uri: string): Promise<Boolean> {
    try {
      await Efb.loadJs(uri);
      return true;
    } catch (error) {
      return error === `${uri} already loaded.`;
    }
  }

  public static registerCommBusListenerAsync(): Promise<CommBusListener> {
    return new Promise((resolve) => {
      const CommBusListener = RegisterCommBusListener(() => {
        resolve(CommBusListener);
      });
    });
  }

  public static makeObservableObject(keyValueObject: any): any {
    const observableEntries = Object.entries(keyValueObject).map(([k, v]) => [k, Subject.create(v)] as const);
    const observableObject = ObjectUtils.fromEntries(observableEntries);
    return observableObject;
  }

}