# Program Listing for File progress.h

↰ [Return to documentation for file](file_icraft-utils_progress.h.md#file-icraft-utils-progress-h) (`icraft-utils\progress.h`)

#pragma once
#include &quot;icraft-utils/logging.h&quot;
#include &quot;icraft-utils/dllexport.h&quot;

namespace icraft {

    class ProgressBar {
    public:
        UTILS_DLL ProgressBar();

        UTILS_DLL explicit ProgressBar(ColorName color);

        UTILS_DLL void setColor(ColorName color);

        UTILS_DLL void setProgress(float progress);

        UTILS_DLL float progress() const;

        UTILS_DLL void tick();

        UTILS_DLL void tick(int progress);

        UTILS_DLL void setPrefixText(const std::string&amp; text);

        UTILS_DLL void setPostfixText(const std::string&amp; text);

        UTILS_DLL void showElapsedTime(bool show);

        UTILS_DLL void showRemainingTime(bool show);

        UTILS_DLL float current();

        UTILS_DLL bool isCompleted();

        UTILS_DLL void markAsCompleted();

        UTILS_DLL ~ProgressBar();

    private:
        struct Impl_BPB;
        std::shared_ptr&lt;Impl_BPB&gt; impl_bpb;

        friend class DynamicProgressBars;
    };

    class DynamicProgressBars {
    public:
        UTILS_DLL DynamicProgressBars(std::vector&lt;ProgressBar&gt; bars);

        UTILS_DLL ProgressBar&amp; operator[](size_t index);

        UTILS_DLL size_t append(ProgressBar&amp; bar);

        UTILS_DLL void hideBarWhenComplete(bool hide);

    private:
        struct Impl_DP;
        std::shared_ptr&lt;Impl_DP&gt; impl_dp;
    };
}
</pre>

                