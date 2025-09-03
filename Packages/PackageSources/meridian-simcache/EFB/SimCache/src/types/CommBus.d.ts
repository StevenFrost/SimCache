/// <reference types="@microsoft/msfs-types/js/common" />

// add `CommBusListener` definition for typescript (since @microsoft/msfs-types does not have definitions for this type)
declare class CommBusListener extends ViewListener.ViewListener {
  callWasm(name: any, jsonBuf: any): Promise<any>;
}

// add `RegisterCommBusListener` definition for typescript (since @microsoft/msfs-types does not have definitions for this type)
declare function RegisterCommBusListener(callback: () => void): CommBusListener;