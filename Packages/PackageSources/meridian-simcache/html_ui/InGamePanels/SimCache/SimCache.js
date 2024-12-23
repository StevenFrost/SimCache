//-----------------------------------------------------------------------------

// matches SimCache\Source\SimCacheModule\Source\Core\TrackerState.h
const TrackerState = Object.freeze({
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
        this.CommBusListener.on("SimCache.TrackerStateUpdatedEvent", this.onTrackerStateUpdatedEvent.bind(this));
        this.CommBusListener.on("SimCache.CacheFoundEvent", this.onCacheFoundEvent.bind(this));
        this.CommBusListener.callWasm("SimCache.TrackerLoadedEvent", "");
    }

    onTrackerStateUpdatedEvent(eventData) {
        if (this.m_timeoutID !== null) {
            this.cancelPendingClose();
        }
        const data = JSON.parse(eventData);
        this.updateUIElements(data.id, data.state);
        this.makeVisible();
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

    updateUIElements(title, trackerStateAnnulus) {
        this.updateCacheTitle(title);
        this.updateCacheRange(trackerStateAnnulus);
    }

    makeVisible() {
        // ensure the panel is visible (since display-none is set in the html upon load)
        // (this is done to prevent the panel from appearing before it's fully initialized)
        this.m_containerElement.classList.remove("display-none");
    }

    updateCacheTitle(title) {
        this.m_titleElement.innerText = title;
    }

    updateCacheRange(trackerStateAnnulus) {
        const piecewiseRange = this.getPiecewiseRange(trackerStateAnnulus);
        this.m_subtitleElement.innerText = this.getSubtitle(piecewiseRange);
        this.m_annulusElement.setAttributeNS(null, "r", this.getAnnulusInnerRadius(trackerStateAnnulus));
    }

    getSubtitle(piecewiseRange) {
        return piecewiseRange !== null ? `Less than ${piecewiseRange} nm away` : "Out of range";
    }

    getPiecewiseRange(trackerStateAnnulus) {
        switch (trackerStateAnnulus) {
            case TrackerState.Annulus1:
                return 2;
            case TrackerState.Annulus2:
                return 5;
            case TrackerState.Annulus3:
                return 10;
            case TrackerState.Annulus4:
                return 25;
            default:
                return null;
        }
    }

    getAnnulusInnerRadius(trackerStateAnnulus) {
        switch (trackerStateAnnulus) {
            case TrackerState.Annulus1:
                return 0;
            case TrackerState.Annulus2:
                return 22;
            case TrackerState.Annulus3:
                return 31;
            case TrackerState.Annulus4:
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
