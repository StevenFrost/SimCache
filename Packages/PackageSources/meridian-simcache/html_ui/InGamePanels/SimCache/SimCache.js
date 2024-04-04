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
        this.CommBusListener.on("SimCache.TrackedCacheDataUpdatedEvent", this.onTrackedCacheDataUpdatedEvent.bind(this));
        this.CommBusListener.on("SimCache.CacheFoundEvent", this.onCacheFoundEvent.bind(this));
        this.CommBusListener.callWasm("SimCache.TrackerLoadedEvent", "");
    }

    onTrackedCacheDataUpdatedEvent(eventData) {
        if (this.m_timeoutID !== null) {
            this.cancelPendingClose();
        }
        const data = JSON.parse(eventData);
        this.m_titleElement.innerText = data.title;
        this.updateRange(data.distance_meters);
        this.m_containerElement.classList.remove("display-none");
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

    updateRange(distanceMeters) {
        const piecewiseRange = this.getPiecewiseRange(distanceMeters);
        this.m_subtitleElement.innerText = this.getSubtitle(piecewiseRange);
        this.m_annulusElement.setAttributeNS(null, "r", this.getAnnulusInnerRadius(piecewiseRange));
    }

    getSubtitle(piecewiseRange) {
        return piecewiseRange !== null ? `Less than ${piecewiseRange} nm away` : "Out of range";
    }

    getPiecewiseRange(distanceMeters) {
        if (distanceMeters < 0) {
            throw new RangeError("Negative distances are not allowed");
        }
        if (distanceMeters < 3704) {
            return 2;
        }
        if (distanceMeters < 9260) {
            return 5;
        }
        if (distanceMeters < 18520) {
            return 10;
        }
        if (distanceMeters < 46300) {
            return 25;
        }
        return null;
    }

    getAnnulusInnerRadius(piecewiseRange) {
        switch (piecewiseRange) {
            case 2:
                return 0;
            case 5:
                return 22;
            case 10:
                return 31;
            case 25:
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
