
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <boost/vmd/assert_is_type.hpp>
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
#if BOOST_PP_VARIADICS

#if BOOST_VMD_ASSERT_DATA
    
  BOOST_VMD_ASSERT_IS_TYPE(10)
  
#else

  typedef char BOOST_VMD_ASSERT_IS_NUMBER_ERROR[-1];
  
#endif

#endif

  return boost::report_errors();
  
  }
