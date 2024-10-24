#ifndef ELO_VIEWCOMPONENTSTATE_H
#define ELO_VIEWCOMPONENTSTATE_H

/**
 * Base class for view component states.
 */
class ViewComponentState {
   public:
    ViewComponentState() = default;

    /**
     * Hides the component.
     */
    virtual void hide() { this->hidden = true; };

    /**
     * Shows the component.
     */
    virtual void show() { this->hidden = false; };

    /**
     * Returns true if the component is hidden.
     */
    [[nodiscard]] virtual bool isHidden() const { return this->hidden; };

    virtual ~ViewComponentState() = default;

   private:
    /**
     * True if the component is hidden.
     */
    bool hidden = false;
};

#endif
