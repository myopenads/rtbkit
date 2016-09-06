/** openrtb_native.h
    Copyright (c) 2013 Datacratic Inc.  All rights reserved.

    This file is part of RTBkit.

    Programmatic Description of the OpenRTB Dynamic Native Ads 1.1 specification.

    Documentation is taken from the OpenRTB Dynamic Native Ads API Specification Version 1.1
    http://www.iab.com/wp-content/uploads/2016/03/OpenRTB-Native-Ads-Specification-1-1_2016.pdf

    That document has the following license:

    OpenRTB Specification by OpenRTB is licensed under a Creative Commons
    Attribution 3.0 License, based on a work at openrtb.info. Permissions
    beyond the scope of this license may be available at http://openrtb.info.
    To view a copy of this license, visit
    http://creativecommons.org/licenses/by/3.0/
    or write to Creative Commons, 171 Second Street, Suite 300, San Francisco,
    CA 94105, USA.
*/

#pragma once

#include "openrtb.h"
#include "openrtb_parsing.h"

namespace OpenRTB {


//using namespace Datacratic;
using Datacratic::Optional;
using Datacratic::List;

/*****************************************************************************/
/* CONTEXT TYPE IDS                                                          */
/*****************************************************************************/

/** 7.3 Context Type IDs

	The context in which the ad appears - what type of content is surrounding the ad on the
	page at a high level. This maps directly to the new Deep Dive on In-Feed Ad Units. This
	denotes the primary context, but does not imply other content may not exist on the
	page - for example it's expected that most content platforms have some social
	components, etc.
*/

struct ContextType: public Datacratic::TaggedEnum<ContextType> {
    enum Vals {
        UNSPECIFIED = -1,  ///< Not explicitly specified

        CONTENT = 1,
        SOCIAL = 2,
        PRODUCT = 3
    };
};

/*****************************************************************************/
/* CONTEXT SUBTYPE IDS                                                       */
/*****************************************************************************/

/** 7.4 Context Sub Type IDs

	Next-level context in which the ad appears. Again this reflects the primary context, and
	does not imply no presence of other elements. For example, an article is likely to
	contain images but is still first and foremost an article. SubType should only be
	combined with the primary context type as indicated (ie for a context type of 1, only
	context subtypes that start with 1 are valid).
*/

struct ContextSubType: public Datacratic::TaggedEnum<ContextSubType> {
    enum Vals {
        UNSPECIFIED = -1,  ///< Not explicitly specified

        GENERAL = 10,
        ARTICLE = 11,
        VIDEO = 12,
        AUDIO = 13,
        IMAGE = 14,
        USER_GENERATED = 15,
        GENERAL_SOCAL = 20,
        EMAIL = 21,
        CHAT_IM = 22,
        PRODUCTS = 30,
        APPSTORE = 31,
        PRODUCT_REVIEW = 32
    };
};

/*****************************************************************************/
/* PLACEMENT TYPE IDS                                                        */
/*****************************************************************************/

/** 7.5 Placement Type IDs

	The FORMAT of the ad you are purchasing, separate from the surrounding context
*/

struct PlacementType: public Datacratic::TaggedEnum<PlacementType> {
    enum Vals {
        UNSPECIFIED = -1,  ///< Not explicitly specified

        FEED = 1,
        ATOMIC = 2,
        CONTENT = 3,
        WIDGET = 4
    };
};

/*****************************************************************************/
/* DATA ASSET TYPE                                                           */
/*****************************************************************************/

/** 7.6 Data Asset Types

	Below is a list of common asset element types of native advertising at the time of
	writing this spec. This list is non-exhaustive and intended to be extended by the buyers
	and sellers as the format evolves. 
*/

struct DataType: public Datacratic::TaggedEnum<DataType> {
    enum Vals {
        UNSPECIFIED = -1,  ///< Not explicitly specified

        SPONSORED = 1, ///< Required. Max 25 or longer
        DESC = 2, ///< Recommended. Max 140 or longer.
        RATING = 3, ///< Optional. 0-5 integer formatted as string.
        LIKES = 4,
        DOWNLOADS = 5,
        PRICE = 6,
        SALE_PRICE = 7,
        PHONE = 8,
        ADDRESS = 9,
        DESC2 = 10,
        DISPLAY_URL = 11,
        CTATEXT = 12 ///< Optional. Max 15 or longer.
    };
};

/*****************************************************************************/
/* IMAGE ASSET TYPE                                                          */
/*****************************************************************************/

/** 7.7 Image Asset Types

	Below is a list of common image asset element types of native advertising at the time of
	writing this spec. This list is non-exhaustive and intended to be extended by the buyers
	and sellers as the format evolves. 
*/

struct ImageType: public Datacratic::TaggedEnum<ImageType> {
	enum Vals {
        UNSPECIFIED = -1,  ///< Not explicitly specified

        ICON = 1,
        LOGO = 2,
        MAIN = 3
    };
};

/*****************************************************************************/
/* TITLE OBJECT                                                              */
/*****************************************************************************/

/** 4.3 Title Object
	The Title object is to be used for title element of the Native ad.
*/

struct NTitle {
    ~NTitle();
	Datacratic::TaggedInt len; ///<Maximum length of the text in the title element.
	Json::Value ext; ///< Placeholder for exchange-specific extensions to OpenRTB
};

/*****************************************************************************/
/* IMAGE OBJECT                                                              */
/*****************************************************************************/

/** 4.4 Image Object
	The Image object to be used for all image elements of the Native ad such as Icons, Main Image,
	etc. Recommended sizes and aspect ratios are included in the Image Asset Types section.
*/

struct NImage {
    ~NImage();
	ImageType type;
	Datacratic::TaggedInt w;
	Datacratic::TaggedInt wmin;
	Datacratic::TaggedInt h;
	Datacratic::TaggedInt hmin;
	Datacratic::List<MimeType> mimes;
	Json::Value ext; ///< Placeholder for exchange-specific extensions to OpenRTB
};

/*****************************************************************************/
/* VIDEO OBJECT                                                              */
/*****************************************************************************/

/** 4.5 Video Object
	The video object to be used for all video elements supported in the Native Ad. This corresponds
	to the Video object of OpenRTB. Exchange implementers can impose their own specific
	restrictions. Here are the required attributes of the Video Object. For optional attributes please
	refer to OpenRTB.
*/

struct NVideo {
    ~NVideo();
	Datacratic::List<MimeType> mimes;
	Datacratic::TaggedFloat minduration;
	Datacratic::TaggedFloat maxduration;
	VideoBidResponseProtocol protocol;
	Json::Value ext; ///< Placeholder for exchange-specific extensions to OpenRTB
};

/*****************************************************************************/
/* DATA OBJECT                                                               */
/*****************************************************************************/

/** 4.6 Data Object

	The Data Object is to be used for all non-core elements of the native unit such as Brand Name,
	Ratings, Review Count, Stars, Download count, descriptions etc. It is also generic for future
	native elements not contemplated at the time of the writing of this document. In some cases,
	additional recommendations are also included in the Data Asset Types table.
*/

struct NData {
    ~NData();
	DataType type;
	Datacratic::TaggedInt len;
	Json::Value ext; ///< Placeholder for exchange-specific extensions to OpenRTB
};

/*****************************************************************************/
/* ASSET                                                                     */
/*****************************************************************************/

struct NAsset {
    ~NAsset();
	Datacratic::Id id; ///< 
	Datacratic::TaggedBoolDef<0> required; ///< 
	NTitle title; ///< Title object for title assets.
	Datacratic::Optional<NImage> img; ///< Image object for image assets.
	Datacratic::Optional<NVideo> video; ///< Video object for video assets.
	Datacratic::Optional<NData> data; ///< Data object for brand name, description, ratings, prices etc.
	Json::Value ext; ///< Placeholder for exchange-specific extensions to OpenRTB
};

/*****************************************************************************/
/* NATIVEREQUEST                                                             */
/*****************************************************************************/

struct NativeRequest {
    ~NativeRequest();
	Datacratic::UnicodeString ver; ///< Version of the Native Markup version in use.
	ContextType contextType; ///< The context in which the ad appears.
	ContextSubType contextSubType; ///< A more detailed context in which the ad appears.
	PlacementType placementType; ///< The design/format/layout of the ad unit being offered.
	Datacratic::TaggedIntDef<1> placementCount; ///< The number of identical placements in this Layout.
	Datacratic::TaggedIntDef<0> seq;  ///< 0 for the first ad, 1 for the second ad, and so on. NOT be used in combination with placementCount
	std::vector<NAsset> assets; ///< An array of Asset Objects. Any bid response must comply with the array of elements expressed in the bid request
    Json::Value ext; ///< Placeholder for exchange-specific extensions to OpenRTB
    Json::Value unparseable;           ///< Unparseable fields get put here
};

} // namespace std
