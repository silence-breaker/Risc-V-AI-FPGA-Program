# Program Listing for File device.h

```cpp
#pragma once
#ifndef XRT_DEVICE_PCH_GUARD
#define XRT_DEVICE_PCH_GUARD
#include <cstdint>
#include <functional>
#include <chrono>
#include <icraft-xrt/base/dllexport.h>
#include <icraft-utils/midware/mutex.hpp>

#include <icraft-xir/base/string.h>
#include <icraft-xir/base/map.h>
#include <icraft-xir/core/data.h>
#include <icraft-xir/core/reflection.h>
#include <vector>
#include <list>
#include <map>

namespace icraft::xrt {
    using icraft::xir::Node;
    using icraft::xir::Handle;
    using icraft::xir::NodeBase;
    using icraft::xir::VirtualBase;
    using icraft::xir::HandleBase;
    using icraft::xir::make_object;
    using icraft::xir::AttrVisitor;
    using icraft::xir::ReduceVisitor;
    using icraft::xir::GetRef;
    using icraft::xir::ObjectRef;
    using icraft::xir::IntImm;

    /*enum class PtrType {
        CPTR,           ///< C指针
        ADDR,           ///< 物理地址
        BOTH            ///< 既包含C指针，又包含物理地址
    };*/
    WISE_ENUM_CLASS(PtrType, CPTR, ADDR, BOTH)



    class MemPtrNode : public NodeBase<MemPtrNode, Node> {
    private:
        uint64_t addr_;
        char* cptr_ = nullptr;
        PtrType ptype_ = PtrType::CPTR;

        friend class MemPtr;

    public:
        XRT_DLL virtual void accept(AttrVisitor& visitor) override;

        XRT_DLL bool reduceAccept(MemPtrNode* other, const ReduceVisitor& reduce) const;
    };

    class MemPtr : public icraft::xir::HandleBase<MemPtr, Handle, MemPtrNode> {
    public:
        MemPtr() = default;

        XRT_DLL MemPtr(void* cptr, uint64_t addr);

        XRT_DLL explicit MemPtr(void* cptr);

        XRT_DLL explicit MemPtr(uint64_t addr);

        XRT_DLL static MemPtr NullPtr();

        XRT_DLL bool isNull() const;

        XRT_DLL char* cptr() const;

        XRT_DLL uint64_t addr() const;

        XRT_DLL PtrType ptype() const;
    };

    XRT_DLL MemPtr operator+(const MemPtr& lhs, uint64_t rhs);
    XRT_DLL MemPtr operator+(uint64_t lhs, const MemPtr& rhs);
    XRT_DLL MemPtr operator-(const MemPtr& lhs, uint64_t rhs);
    XRT_DLL int64_t operator-(const MemPtr& lhs, const MemPtr& rhs);

    XRT_DLL bool operator<(const MemPtr& lhs, const MemPtr& rhs);
    XRT_DLL bool operator<=(const MemPtr& lhs, const MemPtr& rhs);
    XRT_DLL bool operator>(const MemPtr& lhs, const MemPtr& rhs);
    XRT_DLL bool operator>=(const MemPtr& lhs, const MemPtr& rhs);

    class MemChunk;
    class MemChunkNode;
    class MemRegion;
    class MemRegionNode;
    class DeviceNode;
    class Device;

    using FChunkDeleter = std::function<void(const MemPtr&)>;

    class MemManagerNode : public NodeBase<MemManagerNode, Node> {
    protected:
        const MemRegionNode* region = nullptr;
        XRT_DLL MemChunk CreateMemChunk(
            MemPtr begin,
            uint64_t byte_size,
            FChunkDeleter deleter = nullptr,
            bool auto_free = true);

    private:
        virtual void accept(AttrVisitor& visitor) override {};

        virtual MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment) = 0;

        virtual MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free) = 0;

        virtual void free(const MemPtr& ptr) = 0;

        virtual std::vector<MemChunk> getAllMemChunk() const = 0;

        virtual std::map<std::string, ObjectRef>& getMemRegionInfo() const = 0;

        friend class MemManager;
    };

    class MemManager : public VirtualBase<MemManager, Handle, MemManagerNode> {
    public:
        XRT_DLL void _bindMemRegion(const MemRegionNode* region);

        XRT_DLL MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment);

        XRT_DLL MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free);

        XRT_DLL void free(const MemPtr& ptr);

        XRT_DLL std::vector<MemChunk> getAllMemChunk() const;

        XRT_DLL std::optional<MemChunk> getMemChunk(const MemPtr& ptr, uint64_t byte_size) const;

        XRT_DLL std::map<std::string, ObjectRef>& getMemRegionInfo() const;
    };

    class MemRegionNode : public NodeBase<MemRegionNode, Node> {
    public:
        virtual void accept(AttrVisitor& visitor) override {}

    protected:
        const DeviceNode* dev_ = nullptr;
        mutable MemManager mm_;

        XRT_DLL static MemChunk CreateMemChunk(
            MemPtr begin,
            uint64_t byte_size,
            MemRegion region,
            FChunkDeleter deleter = nullptr,
            bool auto_free = true
        );

    private:
        virtual void init() = 0;

        virtual void deinit() = 0;

        virtual void read(char* dest, const MemPtr& src, uint64_t byte_size) const = 0;

        virtual void write(const MemPtr& dest, char* src, uint64_t byte_size) const = 0;

        virtual MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment = 1) const = 0;

        virtual MemChunk malloc(
            MemPtr begin,
            uint64_t byte_size,
            FChunkDeleter deleter,
            bool auto_free
        ) const = 0;

        virtual void free(const MemPtr& src) const = 0;

        virtual void memcpy(const MemPtr& dest, const MemPtr& src, uint64_t byte_size) const = 0;

        XRT_DLL virtual void memcpy(
            const MemPtr& dest_ptr,
            const MemRegion& src_region,
            const MemPtr& src_ptr,
            uint64_t byte_size
        ) const;

        friend class MemRegion;
        friend class MemManagerNode;
    };

    class MemRegion : public VirtualBase<MemRegion, Handle, MemRegionNode> {
    private:
        XRT_DLL void init();

        XRT_DLL void deinit();

        friend class MemChunkNode;
        friend class MemChunk;
        friend class DeviceNode;
        friend class Device;

    public:
        XRT_DLL void free(const MemPtr& src) const;

        XRT_DLL void read(char* dest, const MemPtr& src, uint64_t byte_size) const;

        XRT_DLL void write(const MemPtr& dest, char* src, uint64_t byte_size) const;

        XRT_DLL void memcpy(const MemPtr& dest, const MemPtr& src, uint64_t byte_size) const;

        XRT_DLL void memcpy(
            const MemPtr& dest_ptr,
            const MemRegion& src_region,
            const MemPtr& src_ptr,
            uint64_t byte_size
        ) const;

    public:
        MemRegion() = default;

        XRT_DLL MemChunk malloc(uint64_t byte_size, bool auto_free = true, uint64_t alignment = 1) const;

        XRT_DLL MemChunk malloc(
            MemPtr begin,
            uint64_t byte_size,
            FChunkDeleter deleter = nullptr,
            bool auto_free = true
        ) const;

        XRT_DLL MemRegion& _bindDevice(const DeviceNode* dev);

        XRT_DLL void _bindMemmanager(const MemManagerNode* manager);

        XRT_DLL Device device() const;

        XRT_DLL const MemManager memManager() const;
    };

    class MemChunkNode : public NodeBase<MemChunkNode, Node> {
    public:
        MemPtr begin;
        uint64_t byte_size;
        MemRegion region;

    private:
        FChunkDeleter deleter_;
        bool auto_free_;

        void free();

        friend class MemChunk;
    public:
        XRT_DLL virtual void accept(AttrVisitor& visitor) override;

        bool reduceAccept(MemChunkNode* other, const ReduceVisitor& reduce) const {
            return reduce(begin, other->begin)
                && reduce(byte_size, other->byte_size)
                && reduce(region, other->region);
        }

        XRT_DLL ~MemChunkNode() noexcept;
    };

    class MemChunk : public HandleBase<MemChunk, Handle, MemChunkNode> {
    private:
        XRT_DLL MemChunk(
            MemPtr begin,
            uint64_t byte_size,
            MemRegion region,
            FChunkDeleter deleter = nullptr,
            bool auto_free = true
        );

        friend class MemRegionNode;

    public:
        MemChunk() = default;

        XRT_DLL void read(char* dest, uint64_t src_offset, uint64_t byte_size) const;

        XRT_DLL void write(uint64_t dest_offset, char* src, uint64_t byte_size) const;

        XRT_DLL void copyFrom(uint64_t dest_offset,
            const MemChunk& src_chunk,
            uint64_t src_offset,
            uint64_t byte_size
        ) const;

        XRT_DLL void free();

        XRT_DLL bool isOn(const MemRegion& region) const;

        XRT_DLL void setDeleter(FChunkDeleter deleter_) const;

        XRT_DLL void setAutoFree(bool auto_free) const;
    };

    class RegRegionNode : public NodeBase<RegRegionNode, Node> {
    public:
        virtual void accept(AttrVisitor& visitor) override {}

    protected:
        const DeviceNode* dev_ = nullptr;

    private:
        virtual void init() = 0;

        virtual void deinit() = 0;

        virtual uint64_t read(uint64_t addr, bool relative = false) const = 0;

        virtual void write(uint64_t addr, uint64_t data, bool relative = false) const = 0;

        friend class RegRegion;
    };

    class RegRegion : public HandleBase<RegRegion, Handle, RegRegionNode> {
    private:
        XRT_DLL void init();

        XRT_DLL void deinit();

        friend class DeviceNode;
        friend class Device;
    public:
        XRT_DLL uint64_t read(uint64_t addr, bool relative = false) const;

        XRT_DLL void write(uint64_t addr, uint64_t data, bool relative = false) const;

        XRT_DLL Device device() const;

        XRT_DLL RegRegion& _bindDevice(const DeviceNode* dev);
    };

    namespace utils {
        class UrlParser {
        private:
            std::string url_;
            std::string protocol_;
            std::string device_;
            std::string site_;
            std::unordered_map<std::string, std::string> params_;

        public:
            XRT_DLL UrlParser(const std::string& url);

            XRT_DLL const std::string& url() const;

            XRT_DLL const std::string& protocol() const;

            XRT_DLL const std::string& device() const;

            XRT_DLL const std::string& site() const;

            XRT_DLL const std::unordered_map<std::string, std::string>& params() const;

            XRT_DLL const std::string& getParam(const std::string& key) const;
        };
    }

    class DeviceNode : public NodeBase<DeviceNode, Node> {
    private:
        virtual void initBeforeRegions() = 0;

        virtual void initAfterRegions() = 0;

        virtual void deinitBeforeRegions() = 0;

        virtual void deinitAfterRegions() = 0;

        virtual void reset(int level) = 0;

        virtual bool check(int level) const = 0;

        virtual void showStatus(int level) const = 0;

        virtual std::unordered_map<std::string, std::string> version() const = 0;

    protected:
        std::unordered_map<std::string_view, MemRegion> mem_regions;
        std::unordered_map<std::string_view, RegRegion> reg_regions;
        MemRegion default_mem_region;
        RegRegion default_reg_region;
        std::vector<std::string_view> mregion_names;
        std::vector<std::string_view> rregion_names;

        friend class Device;
    public:
        std::string url;
        std::string protocol;
        std::string device;
        std::string site;
        std::unordered_map<std::string, std::string> params;
        uint64_t wait_time = 10000;

        virtual void accept(AttrVisitor& visitor) override {
            visitor.visit("url", url);
        }
    };

    class Device : public VirtualBase<Device, Handle, DeviceNode> {
    public:
        XRT_DLL static Device Open(const std::string& url);

        XRT_DLL static void Close(Device& device);

        XRT_DLL const MemRegion& defaultMemRegion() const;

        XRT_DLL Device& setDefaultMemRegion(const std::string& region_name);

        XRT_DLL const MemRegion& getMemRegion(const std::string& name) const;

        XRT_DLL MemChunk malloc(uint64_t byte_size) const;

        XRT_DLL MemChunk malloc(const std::string& mem_region, uint64_t byte_size) const;

        XRT_DLL const RegRegion& defaultRegRegion() const;

        XRT_DLL Device& setDefaultRegRegion(const std::string& region_name);

        XRT_DLL const RegRegion& getRegRegion(const std::string& name) const;

        XRT_DLL uint64_t readReg(uint64_t addr, bool relative = false) const;

        XRT_DLL uint64_t readReg(const std::string& region_name, uint64_t addr, bool relative = false) const;

        XRT_DLL void writeReg(uint64_t addr, uint64_t data, bool relative = false) const;

        XRT_DLL void writeReg(const std::string& region_name, uint64_t addr, uint64_t data, bool relative = false) const;

        XRT_DLL void reset(int level);

        XRT_DLL bool check(int level) const;

        XRT_DLL void showStatus(int level) const;

        XRT_DLL std::unordered_map<std::string, std::string> version() const;

        XRT_DLL void setWaitTime(uint64_t wait_time);

    private:
        void initParams(const utils::UrlParser& parser);
        void init();
        void deinit();
    };

    class DeviceRegistry {
    public:
        class Manager;

        using FCreator = std::function<Device()>;

        XRT_DLL DeviceRegistry& set_creator(FCreator f);

        XRT_DLL static DeviceRegistry& Register(std::string_view name, bool can_override = false);

        XRT_DLL static bool Remove(const std::string& name);


        XRT_DLL static std::optional<FCreator> Get(const std::string& name);

        XRT_DLL std::vector<std::string_view> ListNames();

    private:
        FCreator fcreator_;
    };

    class DefaultMemManagerNode : public NodeBase<DefaultMemManagerNode, MemManagerNode> {
    public:
        MemPtr start_;
        uint64_t byte_size_;
        std::list<std::pair<MemPtr, uint64_t>> chunk_list_;
        std::vector<const MemChunkNode*> chunk_node_; //保存const MemChunkNode*避免增加引用计数
        mutable std::map<std::string, ObjectRef> info_;
        mutable midware::Mutex mem_mutex_;

        DefaultMemManagerNode(MemPtr start, uint64_t byte_size) : start_(start), byte_size_(byte_size) {
            info_.insert({"start", start});
            info_.insert({"byte_size", IntImm(byte_size) });
        };

        XRT_DLL virtual MemChunk malloc(uint64_t byte_size, bool auto_free, uint64_t alignment) override;

        XRT_DLL virtual MemChunk malloc(MemPtr begin, uint64_t byte_size, FChunkDeleter deleter, bool auto_free) override;

        XRT_DLL virtual void free(const MemPtr& ptr) override;

        XRT_DLL virtual std::vector<MemChunk> getAllMemChunk() const override;

        XRT_DLL virtual std::map<std::string, ObjectRef>& getMemRegionInfo() const override;

    };

    class  DefaultMemManager : public HandleBase<DefaultMemManager, MemManager, DefaultMemManagerNode> {};

    namespace utils {
        template<typename predicate, typename Rep, typename Period>
        static bool WaitUntil(predicate check, std::chrono::duration<Rep, Period> timeout){
            auto start = std::chrono::system_clock::now();
            while (!check()){
                if(std::chrono::system_clock::now() - start > timeout){return false;}
            }
            return true;
        }
    }
}

#define ICRAFT_DECLARE_DEVICE_NODE(DeviceNode)  DeviceNode()
#define ICRAFT_MEM_REGION_FIELD(RegionName, MemRegionType)              \
    mregion_names.push_back(ICRAFT_STR(RegionName));                    \
    mem_regions[ICRAFT_STR(RegionName)] = MemRegionType::Init()._bindDevice(this)
#define ICRAFT_REG_REGION_FIELD(RegionName, RegRegionType)              \
    rregion_names.push_back(ICRAFT_STR(RegionName));                    \
    reg_regions[ICRAFT_STR(RegionName)] = RegRegionType::Init()._bindDevice(this)

#define ICRAFT_DEFAULT_MEM_REGION_FIELD(RegionName, MemRegionType)      \
    ICRAFT_MEM_REGION_FIELD(RegionName, MemRegionType);                 \
    default_mem_region = mem_regions.at(ICRAFT_STR(RegionName))
#define ICRAFT_DEFAULT_REG_REGION_FIELD(RegionName, RegRegionType)      \
    ICRAFT_REG_REGION_FIELD(RegionName, RegRegionType);                 \
    default_reg_region = reg_regions.at(ICRAFT_STR(RegionName))
#define ICRAFT_REGION_MEM_MANAGER_FIELD(RegionName, MemManagerNode, ...)        \
    mem_regions[ICRAFT_STR(RegionName)]._bindMemmanager(make_object<MemManagerNode>(__VA_ARGS__).get())

#define ICRAFT_DEVICE_REG_VAR_DEF                                                           \
static ICRAFT_ATTRIBUTE_UNUSED ::icraft::xrt::DeviceRegistry __make_device

#define ICRAFT_REGISTER_DEVICE(DeviceHeadURL, DeviceType)                                   \
 ICRAFT_STR_CONCAT(ICRAFT_DEVICE_REG_VAR_DEF, __COUNTER__) =                                \
      ::icraft::xrt::DeviceRegistry::Register(DeviceHeadURL)                                \
.set_creator([](){ return DeviceType::Init(); })

#endif //XRT_DEVICE_PCH_GUARD
```

[Return to documentation for file](file_icraft-xrt_core_device.h.md#file-icraft-xrt-core-device-h)
