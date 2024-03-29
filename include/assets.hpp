#pragma once

#include <string_view>
#include "beatsaber-hook/shared/utils/typedefs.h"

struct IncludedAsset {

    IncludedAsset(uint8_t* start, uint8_t* end) : array(reinterpret_cast<Array<uint8_t>*>(start)) {
        array->klass = nullptr;
        array->monitor = nullptr;
        array->bounds = nullptr;
        array->max_length = end - start - 33;
        *(end - 1)= '\0';
    }
    
    operator ArrayW<uint8_t>() const {
        init();
        return array;
    }

    operator std::string_view() const {
        return { reinterpret_cast<char*>(array->values), array->Length() };
    }
    
    operator std::span<uint8_t>() const {
        return { array->values, array->Length() };
    }

    void init() const {
        if(!array->klass)
            array->klass = classof(Array<uint8_t>*);
    }

    private:
        Array<uint8_t>* array;

};

#define DECLARE_FILE(name)                         \
    extern "C" uint8_t _binary_##name##_start[];  \
    extern "C" uint8_t _binary_##name##_end[];    \
    const IncludedAsset name { _binary_##name##_start, _binary_##name##_end};

namespace IncludedAssets {

	DECLARE_FILE(CreditView_bsml)
	DECLARE_FILE(DeleteIcon_png)
	DECLARE_FILE(DeletionConfirmationModal_bsml)
	DECLARE_FILE(GameplaySetupView_bsml)
	DECLARE_FILE(MenuIcon_png)
	DECLARE_FILE(MenuIconSelected_png)
	DECLARE_FILE(PatronCreditBox_bsml)
	DECLARE_FILE(PlaceHolderImage_png)
	DECLARE_FILE(ProfileSwitcherView_bsml)
	DECLARE_FILE(QosmeticsItemCell_bsml)
	DECLARE_FILE(QosmeticsSettingsButton_bsml)
	DECLARE_FILE(QosmeticsView_bsml)
	DECLARE_FILE(SelectIcon_png)
	DECLARE_FILE(de_xml)
	DECLARE_FILE(en_xml)
	DECLARE_FILE(es_xml)
	DECLARE_FILE(fr_xml)
	DECLARE_FILE(ja_xml)
	DECLARE_FILE(ko_xml)

}
