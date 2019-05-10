#pragma once

#include <map>
#include <memory>
#include <type_traits>
#include <utility>

#include "raw_config_parser.hpp"
#include "toml_utils.hpp"

namespace hatter {
namespace internal {
struct SectionSanitizerError {
   protected:
    bool hasError_ = false;

   public:
    bool hasError() const;
    void setError(const bool error);

    virtual std::string what() = 0;
    virtual ~SectionSanitizerError();
};

struct UnknownValueError : SectionSanitizerError {
    std::vector<std::string> undefinedVals;

    std::string what() override;
};

struct RepoNoLinkError : SectionSanitizerError {
    std::string what() override;
};

struct SubSectionErrorReport {
   protected:
    bool hasError_ = false;

   public:
    std::vector<std::shared_ptr<TOMLError>>             tomlErrors;
    std::vector<std::shared_ptr<SectionSanitizerError>> sanitizerErrors;
    bool                                                hasError() const;

    const std::string sectionName;

    explicit SubSectionErrorReport(const std::string& sectionName);

    template <typename T, std::enable_if_t<std::is_base_of<TOMLError, T>::value>* = nullptr>
    SubSectionErrorReport& operator+=(const std::shared_ptr<T>&& error) {
        if (error->hasError()) {
            hasError_ = true;
            tomlErrors.push_back(error);
        }
        return *this;
    }

    template <typename T,
              std::enable_if_t<std::is_base_of<SectionSanitizerError, T>::value>* = nullptr>
    SubSectionErrorReport& operator+=(const std::shared_ptr<T>&& error) {
        if (error->hasError()) {
            hasError_ = true;
            sanitizerErrors.push_back(error);
        }
        return *this;
    }
};

struct TopSectionErrorReport : SubSectionErrorReport {
    std::vector<SubSectionErrorReport> subSectionErrors;

    explicit TopSectionErrorReport(const std::string& sectionName);

    TopSectionErrorReport& operator+=(const SubSectionErrorReport& error);

    template <typename T, std::enable_if_t<std::is_base_of<TOMLError, T>::value>* = nullptr>
    TopSectionErrorReport& operator+=(const std::shared_ptr<T>&& error) {
        if (error->hasError()) {
            hasError_ = true;
            tomlErrors.push_back(error);
        }
        return *this;
    }

    template <typename T,
              std::enable_if_t<std::is_base_of<SectionSanitizerError, T>::value>* = nullptr>
    TopSectionErrorReport& operator+=(const std::shared_ptr<T>&& error) {
        if (error->hasError()) {
            hasError_ = true;
            sanitizerErrors.push_back(error);
        }
        return *this;
    }
};

TopSectionErrorReport getSection(const toml::table& rawConfig, RepoConfig& repoConfig);
}  // namespace internal
}  // namespace hatter