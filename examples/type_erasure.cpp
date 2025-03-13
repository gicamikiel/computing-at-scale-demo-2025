#include <cmath>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <span>

// type erased integrator type
class Integrator {
   public:
    template <typename T>
    Integrator(T integrator)
        : pimpl_(std::make_unique<IntegratorModel<T>>(integrator)) {}
    [[nodiscard]]
    std::span<const double> GetWeights() const noexcept {
        return pimpl_->GetWeights();
    };
    [[nodiscard]]
    std::span<const double> GetPoints() const noexcept {
        return pimpl_->GetPoints();
    }
    [[nodiscard]] size_t Size() const noexcept { return pimpl_->Size(); }

   private:
    struct IntegratorConcept {
        virtual std::span<const double> GetPoints() const noexcept = 0;
        virtual std::span<const double> GetWeights() const noexcept = 0;
        virtual int Size() const noexcept = 0;
    };

    template <typename T>
    struct IntegratorModel final : IntegratorConcept {
        IntegratorModel(T integrator) : integrator_(integrator) {}
        std::span<const double> GetPoints() const noexcept override {
            return integrator_.GetPoints();
        }
        std::span<const double> GetWeights() const noexcept override {
            return integrator_.GetWeights();
        }
        int Size() const noexcept override { return integrator_.Size(); }
        T integrator_;
    };

    std::unique_ptr<IntegratorConcept> pimpl_;
};

class GaussLagrangeIntegrator {
   public:
    GaussLagrangeIntegrator(int order) {
        switch (order) {
            // 1 point for order 1
            case 1:
                points_ = {0};
                weights_ = {2};
                break;
            // 2 points up to order 3
            case 2:
            case 3:
                points_ = {-1. / sqrt(3), 1. / sqrt(3)};
                weights_ = {1., 1.};
                break;
            // 3 points up to order 5
            case 4:
            case 5:
                points_ = {-sqrt(3. / 5), 0, sqrt(3. / 5)};
                weights_ = {5. / 9, 8. / 9, 5. / 9};
            // 4 points up to order 7
            case 6:
            case 7:
                points_ = {-0.861136, -0.339981, 0.339981, 0.861136};
                weights_ = {0.347855, 0.652145, 0.652145, 0.347855};
            default:
                throw std::runtime_error("only supported up to order 4");
        }
    }

    [[nodiscard]]
    const std::vector<double>& GetWeights() const noexcept {
        return weights_;
    };
    [[nodiscard]]
    const std::vector<double>& GetPoints() const noexcept {
        return points_;
    }
    [[nodiscard]] size_t Size() const noexcept { return weights_.size(); }

   private:
    std::vector<double> points_;
    std::vector<double> weights_;
};


template <int NPts>
class GaussLagrangeIntegratorStaticNPts
{
    static_assert(NPts>0 && NPts<=4, "implemented up to 4 points");
};

constexpr int gauss_lagrange_order_to_num_points(int order) {
    return ceil((order+1.0)/2.0);
}

template <int Order>
using GaussLagrangeIntegratorStatic = GaussLagrangeIntegratorStaticNPts<gauss_lagrange_order_to_num_points(Order)>;


template<>
class GaussLagrangeIntegratorStaticNPts<1> {
    public:
    [[nodiscard]]
    const auto& GetWeights() const noexcept {return weights_;};
    [[nodiscard]]
    const auto& GetPoints() const noexcept {return points_;}
    [[nodiscard]] size_t Size() const noexcept { return weights_.size(); }
    private:
    std::array<double, 1> points_{0};
    std::array<double, 1> weights_{2};
};
template<>
class GaussLagrangeIntegratorStaticNPts<2> {
    public:
    [[nodiscard]]
    const auto& GetWeights() const noexcept {return weights_;};
    [[nodiscard]]
    const auto& GetPoints() const noexcept {return points_;}
    [[nodiscard]] size_t Size() const noexcept { return weights_.size(); }
    private:
    std::array<double, 2> points_{-1. / sqrt(3), 1. / sqrt(3)};
    std::array<double, 2> weights_{1., 1.};
};

template<>
class GaussLagrangeIntegratorStaticNPts<3> {
    public:
    [[nodiscard]]
    const auto& GetWeights() const noexcept {return weights_;};
    [[nodiscard]]
    const auto& GetPoints() const noexcept {return points_;}
    [[nodiscard]] size_t Size() const noexcept { return weights_.size(); }
    private:
    std::array<double, 3> points_{-sqrt(3. / 5), 0, sqrt(3. / 5)};
    std::array<double, 3> weights_{5. / 9, 8. / 9, 5. / 9};
};

template<>
class GaussLagrangeIntegratorStaticNPts<4> {
    public:
    [[nodiscard]]
    const auto& GetWeights() const noexcept {return weights_;};
    [[nodiscard]]
    const auto& GetPoints() const noexcept {return points_;}
    [[nodiscard]] size_t Size() const noexcept { return weights_.size(); }
    private:
    std::array<double, 4> points_{-0.861136, -0.339981, 0.339981, 0.861136};
    std::array<double, 4> weights_{0.347855, 0.652145, 0.652145, 0.347855};
};

double integrate(std::function<double(double)> func, const Integrator& integrator) {
    auto weights = integrator.GetWeights();
    auto points = integrator.GetPoints();
    double value = 0;
    for (size_t i = 0; i < integrator.Size(); ++i) {
        value += func(points[i]) * weights[i];
    }
    return value;
}

int main() {
    std::vector<Integrator> integrators;
    integrators.emplace_back(GaussLagrangeIntegrator{3});
    integrators.emplace_back(GaussLagrangeIntegratorStatic<2>{});
    integrators.emplace_back(GaussLagrangeIntegratorStatic<4>{});
    integrators.emplace_back(GaussLagrangeIntegratorStatic<6>{});
    std::cout<<gauss_lagrange_order_to_num_points(4)<<std::endl;

    for(const auto& integrator : integrators) {
        std::cout<< integrate([](double xi) { return std::pow(xi,0); }, integrator) <<std::endl;
    }

    // show type erased type with T
    // discuss T& Wrapper types
    // in class exercise, write a type erased transformation that performs the mapping
    // https://godbolt.org/z/78TxhK14b
  
}