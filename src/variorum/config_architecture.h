#ifndef CONFIG_ARCHIECTURE_H_INCLUDE
#define CONFIG_ARCHIECTURE_H_INCLUDE

#include <stdint.h>

#include <variorum_config.h>

/// @brief Create a mask from bit m to n (63 >= m >= n >= 0).
///
/// Example: MASK_RANGE(4,2) --> (((1<<((4)-(2)+1))-1)<<(2))
///                              (((1<<          3)-1)<<(2))
///                              ((               4-1)<<(2))
///                              (                  3)<<(2))
///                              (                       24) = b11000
#define MASK_RANGE(m,n) ((((uint64_t)1<<((m)-(n)+1))-1)<<(n))

/// @brief Return the value of x after applying bitmask (m,n) (63 >= m >= n >= 0).
///
/// Example: MASK_RANGE(17,4,2) --> 17&24 = b10001 & b11000 = b10000
#define MASK_VAL(x,m,n) (((uint64_t)(x)&MASK_RANGE((m),(n)))>>(n))

/// @brief List of different granularities of control.
enum ctl_domains_e
{
    THREAD,
    CORE,
    SOCKET,
    NODE,
    TILE,
    UNIQUE, // Each processor core has a separate MSR, or a bit field in an MSR governs only a core independently.
    SHARED // MSR or bit field in an MSR governs the operation of both processor cores.
};

/// @brief List of Intel family and models.
enum intel_arch_e
{
    FM_06_2D = 45,  // Ivy Bridge-E
    FM_06_2A = 42,  // Ivy Bridge-E
    FM_06_3E = 62,  // Ivy Bridge
    FM_06_3A = 58,  // Ivy Bridge
    FM_06_3C = 60,  // Haswell, Haswell-E
    FM_06_45 = 69,  // Haswell, Haswell-E
    FM_06_46 = 70,  // Haswell, Haswell-E
    FM_06_3F = 63,  // Haswell-E
    FM_06_3D = 61,  // Broadwell
    FM_06_47 = 71,  // Broadwell
    FM_06_4F = 79,  // Broadwell
    FM_06_56 = 86,  // Broadwell
    FM_06_4E = 78,  // Skylake
    FM_06_55 = 85,  // Skylake
    FM_06_5E = 94,  // Skylake
    FM_06_8E = 142, // Kaby Lake
    FM_06_9E = 158, // Kaby Lake
    FM_06_57 = 87   // Xeon Phi
};

/// @brief Mapping topology information.
struct map
{
    /// @brief Unique ID of each physical core.
    int physical_core_idx;
};

/// @brief Platform-specific information.
///
/// The intersection of all features on all platforms.
struct platform
{
    /***********************************/
    /* Feature-Based Function Pointers */
    /***********************************/
    /// @brief Function pointer to print out power limits.
    ///
    /// @param [in] long_ver Toggle between CSV formatted and long formatted
    ///        output.
    ///
    /// @return Error code.
    int (*dump_power_limits)(int long_ver);

    /// @brief Function pointer to set a power limit to each socket.
    ///
    /// @param [in] socket_power_limit Desired socket power limit in Watts.
    ///
    /// @return Error code.
    int (*set_each_socket_power_limit)(int socket_power_limit);

    /// @brief Function pointer to print the feature set.
    ///
    /// @return Error code.
    int (*print_features)(void);

    /// @brief Function pointer to print out thermal data.
    ///
    /// @param [in] long_ver Toggle between CSV formatted and long formatted
    ///        output.
    ///
    /// @return Error code.
    int (*dump_thermals)(int long_ver);

    /// @brief Function pointer to print out counter data.
    ///
    /// @param [in] long_ver Toggle between CSV formatted and long formatted
    ///        output.
    ///
    /// @return Error code.
    int (*dump_counters)(int long_ver);

    /// @brief Function pointer to print out clocks data.
    ///
    /// @param [in] long_ver Toggle between CSV formatted and long formatted
    ///        output.
    ///
    /// @return Error code.
    int (*dump_clocks)(int long_ver);

    /// @brief Function pointer to print out power consumption data.
    ///
    /// @param [in] long_ver Toggle between CSV formatted and long formatted
    ///        output.
    ///
    /// @return Error code.
    int (*dump_power)(int long_ver);

    /******************************/
    /* Platform-Specific Topology */
    /******************************/
    /// @brief Unique family and model for Intel architectures.
    uint64_t *intel_arch;
    /// @brief Identifier for AMD architecture.
    uint64_t *amd_arch;
    /// @brief Identifier for IBM architecture.
    uint64_t *ibm_arch;
    /// @brief Identifier for GPU architecture.
    uint64_t *gpu_arch;

    /// @brief Hostname.
    char hostname[1024];
    /// @brief Number of sockets in the node.
    int num_sockets;
    /// @brief Total number of physical cores in the node.
    int total_cores;
    /// @brief Total number of logical threads in the node.
    int total_threads;
    /// @brief Number of physical cores per socket in the node.
    int num_cores_per_socket;
    /// @brief Number of logical threads per core.
    int num_threads_per_core;
    /// @brief Map logical thread ID to physical core ID.
    struct map *map_pu_to_core;
};

#if 0 /* To implement later */
    void (*set_fixed_counters)();
    void (*get_performance_counters)();
    void (*set_performance_counters)();
#endif

struct platform g_platform;

int variorum_enter(const char *filename,
                   const char *func_name,
                   int line_num);

int variorum_exit(const char *filename,
                  const char *func_name,
                  int line_num);

int variorum_get_topology(void);

void variorum_set_topology(int *nsockets,
                           int *ncores,
                           int *nthreads);

int variorum_set_func_ptrs(void);

int variorum_detect_arch(void);

#endif