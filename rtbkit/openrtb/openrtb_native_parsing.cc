/* openrtb_native_parsing.cc
   Jeremy Barnes, 22 February 2013
   Copyright (c) 2013 Datacratic Inc.  All rights reserved.

   Structure descriptions for OpenRTB Native.
*/

#include "openrtb_native_parsing.h"
#include "soa/types/json_parsing.h"

using namespace OpenRTB;
using namespace std;

namespace Datacratic {

DefaultDescription<NativeRequest>::
DefaultDescription()
{
    onUnknownField = [=] (NativeRequest * br, JsonParsingContext & context)
        {
            //cerr << "got unknown field " << context.printPath() << endl;

            std::function<Json::Value & (int, Json::Value &)> getEntry
            = [&] (int n, Json::Value & curr) -> Json::Value &
            {
                if (n == context.path.size())
                    return curr;
                else if (context.path[n].index != -1)
                    return getEntry(n + 1, curr[context.path[n].index]);
                else return getEntry(n + 1, curr[context.path[n].fieldName()]);
            };

            getEntry(0, br->unparseable)
                = context.expectJson();
        };

    addField("id", &NativeRequest::ver, "Native Request Version");
    addField("context", &NativeRequest::contextType, "Context of ad");
    addField("contextsubtype", &NativeRequest::contextSubType, "Detail context of ad");
    addField("plcmttype", &NativeRequest::placementType, "Placement Type");
    addField("plcmtcnt ", &NativeRequest::placementCount, "Placement Count");
    addField("seq", &NativeRequest::seq, "Sequence of ad");
    addField("assets", &NativeRequest::assets, "Array of NAssets object");
    addField("ext", &NativeRequest::ext, "Extended request attributes");

    addField("unparseable", &NativeRequest::unparseable, "Unparseable fields are stored here");
}

DefaultDescription<OpenRTB::NAsset>::
DefaultDescription()
{
    addField("id", &NAsset::id, "Asset ID",
             new StringIdDescription());
    addField("required", &NAsset::required, "Set if this assets is required");
    addField("title", &NAsset::title, "Title object");
    addField("img", &NAsset::img, "Image object");
    addField("video", &NAsset::video, "Video object");
    addField("data", &NAsset::data, "Data object");
    addField("ext", &NAsset::ext, "Extended asset attributes");
}

DefaultDescription<OpenRTB::NData>::
DefaultDescription()
{
    addField("type", &NData::type, "Tyep of data");
    addField("len", &NData::len, "Max length of data");
    addField("ext", &NData::ext, "Extensions to the protocol go here");
}

DefaultDescription<OpenRTB::NImage>::
DefaultDescription()
{
    addField("type", &NImage::type, "Tyep of image");
    addField("h", &NImage::hmin, "Ad height");
    addField("hmin", &NImage::hmin, "Ad minimum height");
    addField("w", &NImage::wmin, "Ad width");
    addField("wmin", &NImage::wmin, "Ad minimum width");
    addField("mimes", &NImage::mimes, "Whitelist of content MIME types (none = all)");
    addField("ext", &NImage::ext, "Extensions to the protocol go here");
}

DefaultDescription<OpenRTB::NVideo>::
DefaultDescription()
{
    addField("mimes", &NVideo::mimes, "Content MIME types supported");
    addField("minduration", &NVideo::minduration, "Minimum duration in seconds");
    addField("maxduration", &NVideo::maxduration, "Maximum duration in seconds");
    addField("protocols", &NVideo::protocols, "Bid response supported protocols");
    addField("ext", &NVideo::ext, "Extensions to the protocol go here");
}

DefaultDescription<OpenRTB::NTitle>::
DefaultDescription()
{
    addField("len", &NTitle::len, "Max length of title");
    addField("ext", &NTitle::ext, "Extensions to the protocol go here");
}


} // namespace Datacratic
