namespace magma::core
{
template<class T>
constexpr hash_t hash(T x) noexcept
{
    ConstexprHash<T> hasher;
    return hasher(x);
}

template<class T>
constexpr hash_t hash(T *p) noexcept
{
    ConstexprHash<uintptr_t> hasher;
    return hasher(reinterpret_cast<uintptr_t>(p));
}

template<class T>
constexpr hash_t hashArg(hash_t seed, const T& arg) noexcept
{
    return hashCombine(seed, hash(arg));
}

template<class T, typename... Args>
constexpr hash_t hashArg(hash_t seed, const T& arg, Args... args) noexcept
{
    hash_t value = hashCombine(seed, hash(arg));
    return hashArg(value, args...);
}

template<class T, typename... Args>
constexpr hash_t hashArgs(const T& arg, Args... args) noexcept
{
    return hashArg(hash(arg), args...);
}

template<class T, std::size_t N>
constexpr hash_t hashArray(const T (&arr)[N]) noexcept
{
    return hashing::Fnv1a<T, N, N>().hash(arr);
}

template<class T>
inline hash_t hashArray(const T arr[], std::size_t count) noexcept
{
    std::hash<T> hasher;
    hash_t hash = hasher(arr[0]);
    for (std::size_t i = 1; i < count; ++i)
        hash = hashCombine(hash, hasher(arr[i]));
    return hash;
}

inline hash_t hashString(const char *str) noexcept
{
    assert(str);
    constexpr uint64_t Prime = 1099511628211ull;
    constexpr uint64_t Basis = 14695981039346656037ull;
    hash_t hash = Basis;
    for (size_t i = 0, n = strlen(str); i < n; ++i)
        hash = (hash ^ str[i]) * Prime;
    return hash;
}
} // namespace magma::core
