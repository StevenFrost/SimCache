//-----------------------------------------------------------------------------

// matches SimCache\Source\SimCacheModule\Source\Core\RangeAnnulus.h
const RangeAnnulus = Object.freeze({
    Annulus1: 0, // innermost
    Annulus2: 1,
    Annulus3: 2,
    Annulus4: 3, // outermost
    OutOfRange: 4
});

//-----------------------------------------------------------------------------

class SimCachePanel extends UIElement {
    constructor() {
        super();
    }

    connectedCallback() {
        this.m_timeoutID = null;

        this.m_ingameUI = this.querySelector("ingame-ui");
        this.m_containerElement = document.getElementById("simcache-container");
        this.m_titleElement = document.getElementById("cache-title");
        this.m_subtitleElement = document.getElementById("cache-subtitle");
        this.m_annulusElement = document.getElementById("inner-annulus");
        this.m_greenCircleElement = document.getElementById("green-circle");
        this.m_centralElement = document.getElementById("central");

        Promise.all([
            this.registerCommBusListenerAsync()
        ]).then((values) => this.onSubsystemsInitialized());
    }

    registerCommBusListenerAsync() {
        return new Promise((resolve) => {
            this.CommBusListener = RegisterCommBusListener(resolve)
        });
    }

    onSubsystemsInitialized() {
        this.CommBusListener.on("SimCache.UITrackerDataUpdateEvent", this.onTrackerDataUpdateEvent.bind(this));
        this.CommBusListener.on("SimCache.UIRangeAnnulusChangedEvent", this.onRangeAnnulusChangedEvent.bind(this));
        this.CommBusListener.on("SimCache.UICacheFoundEvent", this.onCacheFoundEvent.bind(this));
        this.CommBusListener.callWasm("SimCache.UITrackerLoadedEvent", "");
    }

    onTrackerDataUpdateEvent(eventData) {
        if (this.m_timeoutID !== null) {
            this.cancelPendingClose();
        }
        const data = JSON.parse(eventData);
        this.updateCacheTitle(data.name);
        this.updateCacheRange(data.annulus);
        this.makeVisible();
    }

    onRangeAnnulusChangedEvent(eventData) {
        if (this.m_timeoutID !== null) {
            // if we somehow get an event while we're waiting for the timeout, just ingore the event
            // (the timeout only gets set after the cache is collected, and if there hasn't been a new tracked cache,
            //  it doesn't make sense to replace the "Cache collected" text)
            return;
        }
        const data = JSON.parse(eventData);
        this.updateCacheRange(data.annulus);
    }

    cancelPendingClose() {
        clearInterval(this.m_timeoutID);
        this.m_timeoutID = null;
        this.m_greenCircleElement.setAttributeNS(null, "r", 0);
        this.m_centralElement.className = "airplane";
        this.m_centralElement.innerHTML = "";
    }

    onCacheFoundEvent(data) {
        this.m_greenCircleElement.setAttributeNS(null, "r", 49);
        this.m_subtitleElement.innerText = "Cache collected";
        this.m_centralElement.className = "checkmark";
        this.m_centralElement.innerHTML = "&#10004;";
        this.m_timeoutID = setTimeout(() => {
            this.m_ingameUI.closePanel();
        }, 5000);
    }

    makeVisible() {
        // ensure the panel is visible (since display-none is set in the html upon load)
        // (this is done to prevent the panel from appearing before it's fully initialized)
        this.m_containerElement.classList.remove("display-none");
    }

    updateCacheTitle(title) {
        this.m_titleElement.innerText = title;
    }

    updateCacheRange(rangeAnnulus) {
        const rangeNauticalMiles = this.getRangeNauticalMiles(rangeAnnulus);
        this.m_subtitleElement.innerText = this.getSubtitle(rangeNauticalMiles);
        this.m_annulusElement.setAttributeNS(null, "r", this.getAnnulusInnerRadius(rangeAnnulus));
    }

    getSubtitle(rangeNauticalMiles) {
        return rangeNauticalMiles !== null ? `Less than ${rangeNauticalMiles} NM away` : "Out of range";
    }

    getRangeNauticalMiles(rangeAnnulus) {
        switch (rangeAnnulus) {
            case RangeAnnulus.Annulus1:
                return 2;
            case RangeAnnulus.Annulus2:
                return 5;
            case RangeAnnulus.Annulus3:
                return 10;
            case RangeAnnulus.Annulus4:
                return 25;
            default:
                return null;
        }
    }

    getAnnulusInnerRadius(rangeAnnulus) {
        switch (rangeAnnulus) {
            case RangeAnnulus.Annulus1:
                return 0;
            case RangeAnnulus.Annulus2:
                return 22;
            case RangeAnnulus.Annulus3:
                return 31;
            case RangeAnnulus.Annulus4:
                return 40;
            default:
                return 49;
        }
    }

}

//-----------------------------------------------------------------------------

window.customElements.define("ingamepanel-simcache", SimCachePanel);
checkAutoload();

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
