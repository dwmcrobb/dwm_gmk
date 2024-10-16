extern "C" {

    #include <gnumake.h>
    
    extern int plugin_is_GPL_compatible;

    int dwm_gmk_setup(const gmk_floc *floc);
    char *dwm_gmk_dirfiles(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_relpath(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_thisdir(const char *name, unsigned int argc, char *argv[]);

}
