#ifndef x264_c_cofnig
#define x264_c_cofnig

//#define X264_MEMORY_MONITOR //for memory leak test
#define TRACE               0

#if (TARGET_IS_IPHONE)
#define ENABLE_WIN32            0
#define ENABLE_IOS              1
#define ENABLE_ANDROID          0
#elif (ANDROID)
#define ENABLE_WIN32            0
#define ENABLE_IOS              0
#define ENABLE_ANDROID          1
#else //WIN32
#define ENABLE_WIN32            1
#define ENABLE_IOS              0
#define ENABLE_ANDROID          0
#endif

#define HAVE_MALLOC_H           ENABLE_ANDROID
#define HAVE_MMX                ENABLE_WIN32
#define ARCH_X86                ENABLE_WIN32
#define SYS_LINUX               !ENABLE_WIN32
#define SYS_WINDOWS             ENABLE_WIN32
#define HAVE_POSIXTHREAD        !ENABLE_WIN32
#define HAVE_CPU_COUNT          ENABLE_WIN32
#define HAVE_LOG2F              ENABLE_IOS
#define HAVE_WIN32THREAD        ENABLE_WIN32

#if TARGET_IPHONE_SIMULATOR
#define ARCH_ARM                0
#define HAVE_ARMV6              0
#define HAVE_ARMV6T2            0
#define HAVE_NEON               0
#else
#define ARCH_ARM                1//!ENABLE_WIN32
#define HAVE_ARMV6              0//!ENABLE_WIN32
#define HAVE_ARMV6T2            0
#define HAVE_NEON               0//!ENABLE_WIN32
#define ARCH_AARCH64            !ENABLE_WIN32
#endif

#if (TARGET_IS_MAC)
#define HAVE_MALLOC_H           0
#define HAVE_MMX                0
#define ARCH_X86                1
#define SYS_LINUX               1
#define SYS_WINDOWS             0
#define HAVE_POSIXTHREAD        1
#define HAVE_CPU_COUNT          0
#define HAVE_LOG2F              1
#define HAVE_WIN32THREAD        0
#define ARCH_ARM                0
#define HAVE_ARMV6              0
#define HAVE_ARMV6T2            0
#define HAVE_NEON               0
#endif

#define HAVE_THREAD             1
#define HAVE_VECTOREXT          0
#define BROKEN_STACK_ALIGNMENT  1
//#define fseek fseeko
//#define ftell ftello
#define HAVE_GPL                0
#define HAVE_INTERLACED         1
#define HAVE_ALTIVEC            0
#define HAVE_ALTIVEC_H          0

#define HAVE_BEOSTHREAD         0
#define HAVE_VISUALIZE          0
#define HAVE_SWSCALE            0
#define HAVE_LAVF               0
#define HAVE_FFMS               0
#define HAVE_GPAC               0
#define HAVE_GF_MALLOC          0
#define HAVE_AVS                0

#endif

