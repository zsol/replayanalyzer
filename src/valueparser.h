#ifndef VALUEPARSER_H
#define VALUEPARSER_H

#include <boost/spirit/include/qi_parse.hpp>

namespace sc2replay { namespace value_parser 
    {
        BOOST_SPIRIT_TERMINAL(value);

        struct value_parser
            : boost::spirit::qi::primitive_parser<value_parser>
        {
            template <typename Context, typename Iterator>
            struct attribute
            {
                typedef int type;
            };

            template <typename Iterator, typename Context, 
                      typename Skipper, typename Attribute>
            bool parse(Iterator& first, Iterator const& last, Context&,
                       Skipper const& skipper, Attribute& attr) const
                {
                    boost::spirit::qi::skip_over(first, last, skipper);

                    if (first == last)
                        return false;

                    int tmp = *first++;
                    if (0<(tmp & 0xc0))
                    {
                        if (first == last)
                            return false;
                        tmp >>= 2;
                        tmp += *first++ << 8;
                    }
                    else
                    {
                        tmp = tmp & 0x3f;
                    }
                    boost::spirit::traits::assign_to(tmp, attr);
                    return true;
                }

            template <typename Context>
            boost::spirit::info what(Context&) const
                {
                    return boost::spirit::info("value");
                }
        };
    }}

namespace boost { namespace spirit 
    {
        template<>
        struct use_terminal<qi::domain, sc2replay::value_parser::tag::value>
            : mpl::true_
        {};

        namespace qi
        {
            template <typename Modifiers>
            struct make_primitive<sc2replay::value_parser::tag::value, Modifiers>
            {
                typedef sc2replay::value_parser::value_parser result_type;

                result_type operator()(unused_type, unused_type) const
                    {
                        return result_type();
                    }
            };
        }
    }}




#endif

// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:
