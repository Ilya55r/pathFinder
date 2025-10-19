#include <QtCore/QtGlobal>
# if defined(GRIDERSHAREDLIB_LIBRARY)
# define GRIDSHAREDLIB_EXPORT Q_DECL_EXPORT
#else
# define GRIDSHAREDLIB_EXPORT Q_DECL_IMPORT
#endif
