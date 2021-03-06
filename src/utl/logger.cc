
#include "utl/logger.hh"

namespace utl::logger {

namespace detail {

result<void> output_base::write(utl::string_view const& s) const {
    utl::maybe_unused(s);
    return utl::success();
}

static output_base const * global_output = nullptr;

output_base const * get_global_output() {
    return global_output;
}

} //namespace detail


push_output::push_output(detail::output_base const* output) 
    : m_previous_output{detail::global_output} {
    detail::global_output = output;
}

push_output::~push_output() {
    detail::global_output = m_previous_output;
}

} //namespace utl::logger

namespace utl {

void log(utl::string_view const& str) {
    if(str.size() == 0 or str.size() == npos) return;
    auto res = logger::detail::get_global_output()->write(str);
    ignore_result(res);
    ignore_result(logger::detail::get_global_output()->write("\r\n"_sv));
}

}


