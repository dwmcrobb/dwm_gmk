#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
std::vector<dwm_gmk_fn_entry>  dwm_gmk_function_entries = {
  { "dwm_bison",      dwm_gmk_bison,      1, 0, GMK_FUNC_DEFAULT  },
  { "dwm_cppdeps",    dwm_gmk_cppdeps,    4, 5, GMK_FUNC_DEFAULT  },
  { "dwm_curpath",    dwm_gmk_curpath,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_cwd",        dwm_gmk_curpath,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_files",      dwm_gmk_files,      0, 2, GMK_FUNC_DEFAULT  },
  { "dwm_flex",       dwm_gmk_flex,       1, 0, GMK_FUNC_DEFAULT  },
  { "dwm_fromtop",    dwm_gmk_fromtop,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_include",    dwm_gmk_include,    1, 0, GMK_FUNC_DEFAULT  },
  { "my",             dwm_gmk_my,         1, 1, GMK_FUNC_NOEXPAND },
  { "myns",           dwm_gmk_myns,       0, 1, GMK_FUNC_DEFAULT  },
  { "myvn",           dwm_gmk_myvn,       0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_push",       dwm_gmk_push,       0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_popf",       dwm_gmk_popf,       1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_popb",       dwm_gmk_popb,       1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_pwd",        dwm_gmk_pwd,        0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_relpath",    dwm_gmk_relpath,    2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_relpwd",     dwm_gmk_relpwd,     1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_reverse",    dwm_gmk_reverse,    1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_rgxmatch",   dwm_gmk_rgxmatch,   2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_rgxreplace", dwm_gmk_rgxreplace, 3, 3, GMK_FUNC_DEFAULT  },
  { "dwm_rgxsearch",  dwm_gmk_rgxsearch,  2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_rgxsubst",   dwm_gmk_rgxsubst,   3, 3, GMK_FUNC_DEFAULT  },
  { "dwm_rotl",       dwm_gmk_rotl,       1, 2, GMK_FUNC_DEFAULT  },
  { "dwm_rotr",       dwm_gmk_rotr,       1, 2, GMK_FUNC_DEFAULT  },
  { "dwm_settop",     dwm_gmk_settop,     0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_sort",       dwm_gmk_sort,       1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_subdirs",    dwm_gmk_subdirs,    0, 2, GMK_FUNC_DEFAULT  },
  { "dwm_thisdir",    dwm_gmk_thisdir,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_top",        dwm_gmk_top,        0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_totop",      dwm_gmk_totop,      0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_uniqleft",   dwm_gmk_uniqleft,   1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_uniqright",  dwm_gmk_uniqright,  1, 1, GMK_FUNC_DEFAULT  }
};
