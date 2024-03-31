//-----------------------------------------------------------------------------

class SimCachePanel extends UIElement {
    constructor() {
        super();
        this.m_connected = false;
    }

    connectedCallback() {
        this.m_connected = true;

        this.m_titleElement = document.getElementById("cache-title");
        this.m_subtitleElement = document.getElementById("cache-subtitle");
        this.m_annulusElement = document.getElementById("inner-annulus");

        this.CommBusListener = RegisterCommBusListener(this.onCommBusListenerRegistered.bind(this));

        // TODO: remove placeholder when CacheDataChangedEvent is set up
        this.updateCacheTitle("Cache Title Placeholder");
        this.updateRange(100000);

        let updateLoop = () => {
            if (!this.m_connected) {
                return;
            }

            try {
                this.UpdatePanel();
            }
            catch (Error) {
                console.error(document.title + " : " + Error);
            }
            requestAnimationFrame(updateLoop);
        };
        requestAnimationFrame(updateLoop);
    }

    onCommBusListenerRegistered() {
        this.CommBusListener.callWasm("SimCache.TrackerLoadedEvent", "");
    }

    updateCacheTitle(title) {
        this.m_titleElement.innerText = title;
    }

    updateRange(distanceMeters) {
        const piecewiseRange = this.getPiecewiseRange(distanceMeters);
        if (this.m_currentPiecewiseRange !== piecewiseRange) {
            this.m_currentPiecewiseRange = piecewiseRange;

            // entered a new annulus; update things as necessary
            this.m_subtitleElement.innerText = this.getSubtitle(piecewiseRange);
            this.m_annulusElement.setAttributeNS(null, "r", this.getAnnulusInnerRadius(piecewiseRange));
        }
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

    UpdatePanel() {
        // TODO: add items to repeat within update loop
    }

}

//-----------------------------------------------------------------------------

window.customElements.define("ingamepanel-simcache", SimCachePanel);
checkAutoload();

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
