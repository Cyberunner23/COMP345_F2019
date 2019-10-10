#pragma once

#include "boost/archive/xml_iarchive.hpp"
#include "boost/archive/xml_oarchive.hpp"
#include "boost/serialization/list.hpp"
#include "boost/serialization/string.hpp"
#include <boost/serialization/vector.hpp>
#include "boost/serialization/nvp.hpp"
#include "boost/serialization/map.hpp"

#define SERIALIZE(var, code) friend class boost::serialization::access; template <class Archive> void serialize(Archive& var, const unsigned int version) code
#define SERIALIZE_CLEANUP(type) BOOST_CLASS_IMPLEMENTATION(type, boost::serialization::object_serializable ) \
                                BOOST_CLASS_TRACKING(type, boost::serialization::track_never )
#define SERIALIZE_IMPLEMENT_STREAM(type) \
static std::ostream& operator<<(std::ostream &oStream, const type &val) \
{ \
    boost::archive::xml_oarchive oArchive(oStream, boost::archive::no_header); \
    oArchive << boost::serialization::make_nvp(BOOST_PP_STRINGIZE(type), val); \
    return oStream; \
} \
static std::istream& operator>>(std::istream &iStream, type &val) \
{ \
    boost::archive::xml_iarchive iArchive(iStream, boost::archive::no_header); \
    iArchive >> boost::serialization::make_nvp(BOOST_PP_STRINGIZE(type), val); \
    return iStream; \
}

template<class T>
inline const boost::serialization::nvp<T> NameValuePair(const char* name, T& t)
{
    return boost::serialization::make_nvp(name, t);
}