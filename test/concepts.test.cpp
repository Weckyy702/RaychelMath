#include "RaychelMath/concepts.h"
#include <random>
#include <vector>
#include "catch2/catch.hpp"

//NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("Raychel::Arithmetic", "[RaychelMath][Concepts]")
{
    using namespace Raychel;

    REQUIRE(Arithmetic<bool>);

    REQUIRE(Arithmetic<char>);
    REQUIRE(Arithmetic<unsigned char>);

    REQUIRE(Arithmetic<short>);
    REQUIRE(Arithmetic<unsigned short>);

    REQUIRE(Arithmetic<int>);
    REQUIRE(Arithmetic<unsigned int>);

    REQUIRE(Arithmetic<long>);
    REQUIRE(Arithmetic<unsigned long>);

    REQUIRE(Arithmetic<long long>);
    REQUIRE(Arithmetic<unsigned long long>);

    REQUIRE(!Arithmetic<std::vector<int>>);
    REQUIRE(!Arithmetic<std::default_random_engine>);
}

//NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("Raychel::StdRandomNumberEngine", "[RaychelMath][Concepts]")
{
    using Raychel::StdRandomNumberEngine;
    REQUIRE(StdRandomNumberEngine<std::minstd_rand0>);
    REQUIRE(StdRandomNumberEngine<std::minstd_rand>);
    REQUIRE(StdRandomNumberEngine<std::mt19937>);
    REQUIRE(StdRandomNumberEngine<std::mt19937_64>);
    REQUIRE(StdRandomNumberEngine<std::ranlux24_base>);
    REQUIRE(StdRandomNumberEngine<std::ranlux48_base>);
    REQUIRE(StdRandomNumberEngine<std::ranlux24>);
    REQUIRE(StdRandomNumberEngine<std::ranlux48>);
    REQUIRE(StdRandomNumberEngine<std::knuth_b>);
    REQUIRE(StdRandomNumberEngine<std::default_random_engine>);

    constexpr auto best_rng_ever = []() -> std::uint32_t { return 42u; };
    REQUIRE(!StdRandomNumberEngine<decltype(best_rng_ever)>);
    REQUIRE(!StdRandomNumberEngine<unsigned int>);
}

//NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("Raychel::StdRandomNumberDistribution", "[RaychelMath][Concepts]")
{
    using Raychel::StdRandomNumberDistribution;

    REQUIRE(StdRandomNumberDistribution<std::uniform_int_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::uniform_real_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::bernoulli_distribution>);
    REQUIRE(StdRandomNumberDistribution<std::binomial_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::negative_binomial_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::geometric_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::poisson_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::exponential_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::gamma_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::weibull_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::extreme_value_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::normal_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::lognormal_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::chi_squared_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::cauchy_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::fisher_f_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::student_t_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::discrete_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std::piecewise_constant_distribution<>>);
    REQUIRE(StdRandomNumberDistribution<std:: piecewise_linear_distribution<>>);

    constexpr auto best_distribution_ever = [](auto rng) { return rng(); };
    REQUIRE(!StdRandomNumberDistribution<decltype(best_distribution_ever)>);
    REQUIRE(!StdRandomNumberDistribution<unsigned long>);
}