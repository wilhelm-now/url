//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_IMPL_AUTHORITY_RULE_IPP
#define BOOST_URL_IMPL_AUTHORITY_RULE_IPP

#include <boost/url/rfc/authority_rule.hpp>
#include <boost/url/grammar/parse.hpp>
#include <boost/url/rfc/host_rule.hpp>
#include <boost/url/rfc/port_rule.hpp>
#include <boost/url/rfc/userinfo_rule.hpp>

namespace boost {
namespace urls {

bool
parse(
    char const*& it,
    char const* const end,
    error_code& ec,
    authority_rule& t)
{
    using grammar::parse;
    auto start = it;

    // [ userinfo "@" ]
    if(parse(it, end, ec,
        t.userinfo, '@'))
    {
        t.has_userinfo = true;
        start = it;
    }
    else
    {
        // rewind
        t.has_userinfo = false;
        it = start;
        ec = {};
    }

    // host
    if(! parse(it, end, ec,
            t.host))
        return false;

    // [ ":" port ]
    if(! parse(it, end, ec,
            t.port))
        return false;

    return true;
}

} // urls
} // boost

#endif
