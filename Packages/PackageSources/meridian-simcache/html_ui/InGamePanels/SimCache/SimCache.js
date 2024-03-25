//-----------------------------------------------------------------------------

class SimCachePanel extends UIElement {
    constructor() {
        super();
        this.m_connected = false;
    }

    connectedCallback() {
        this.m_connected = true;

        this.m_ingameUI = this.querySelector( "ingame-ui" );
        this.m_ingameUI.addEventListener( "panelActive", () => this.onPanelActive() );

        let updateLoop = () => {
            if ( !this.m_connected ) {
                return;
            }

            try {
                this.UpdatePanel();
            }
            catch ( Error ) {
                console.error( document.title + " : " + Error );
            }
            requestAnimationFrame( updateLoop );
        };
        requestAnimationFrame( updateLoop );
    }

    onPanelActive() {
        // TODO: add initialization on panel active
    }

    UpdatePanel() {
        if ( !SimVar.IsReady() ) {
            return;
        }

        // TODO: add items to repeat within update loop
    }

}

//-----------------------------------------------------------------------------

window.customElements.define( "ingamepanel-simcache", SimCachePanel);
checkAutoload();

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
