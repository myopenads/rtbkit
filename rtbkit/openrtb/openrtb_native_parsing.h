/* openrtb_native_parsing.h                                               -*- C++ -*-
   Jeremy Barnes, 22 February 2013
   Copyright (c) 2013 Datacratic Inc.  All rights reserved.

   Code to parse OpenRTB native bid requests.
*/

#pragma once

#include "soa/types/value_description.h"
#include "soa/types/basic_value_descriptions.h"
#include "soa/types/json_parsing.h"
#include "openrtb_native.h"
#include <boost/lexical_cast.hpp>

namespace Datacratic {

template<>
struct DefaultDescription<OpenRTB::NativeRequest>
    : public StructureDescription<OpenRTB::NativeRequest> {
    DefaultDescription();
};

template<>
struct DefaultDescription<OpenRTB::NAsset>
    : public StructureDescription<OpenRTB::NAsset> {
    DefaultDescription();
};

template<>
struct DefaultDescription<OpenRTB::NData>
    : public StructureDescription<OpenRTB::NData> {
    DefaultDescription();
};

template<>
struct DefaultDescription<OpenRTB::NVideo>
    : public StructureDescription<OpenRTB::NVideo> {
    DefaultDescription();
};

template<>
struct DefaultDescription<OpenRTB::NImage>
    : public StructureDescription<OpenRTB::NImage> {
    DefaultDescription();
};

template<>
struct DefaultDescription<OpenRTB::NTitle>
    : public StructureDescription<OpenRTB::NTitle> {
    DefaultDescription();
};

} // namespace Datacratic
