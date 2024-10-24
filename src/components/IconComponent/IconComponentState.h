//
// Created by jieggii on 10/12/24.
//

#ifndef ICONCOMPONENTSTATE_H
#define ICONCOMPONENTSTATE_H

#include <ViewComponentState.h>
#include <cstdint>

class IconComponentState final : public ViewComponentState {
   public:
    explicit IconComponentState(const uint8_t iconID) : iconID(iconID) {}

    /**
     * Set the icon ID of the icon component.
     * @param iconID The icon ID to set.
     */
    void setIconID(uint8_t iconID);

    /**
     * Get the icon ID of the icon component.
     */
    [[nodiscard]] uint8_t getIconID() const;

   private:
    /**
     * The icon ID of the icon component.
     */
    uint8_t iconID;
};

#endif  // ICONCOMPONENTSTATE_H
