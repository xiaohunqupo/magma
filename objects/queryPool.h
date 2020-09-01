/*
Magma - abstraction layer to facilitate usage of Khronos Vulkan API.
Copyright (C) 2018-2020 Victor Coda.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#include "nondispatchable.h"

namespace magma
{
    /* An object that contains a number of query entries
       and their associated state and results.
       Queries are managed using query pool objects. */

    class QueryPool : public NonDispatchable<VkQueryPool>
    {
    public:
        ~QueryPool();
        virtual std::vector<uint64_t> getResults(uint32_t firstQuery,
            uint32_t queryCount,
            bool wait) const noexcept;
        VkQueryType getType() const noexcept { return queryType; }
        uint32_t getQueryCount() const noexcept { return queryCount; }

    protected:
        explicit QueryPool(VkQueryType queryType,
            std::shared_ptr<Device> device,
            uint32_t queryCount,
            VkQueryPipelineStatisticFlags pipelineStatistics,
            std::shared_ptr<IAllocator> allocator);

    protected:
        VkQueryType queryType;
        uint32_t queryCount;
    };

    /* Occlusion queries track the number of samples that pass
       the per-fragment tests for a set of drawing commands.
       The application can then use these results to inform
       future rendering decisions. */

    class OcclusionQuery : public QueryPool
    {
    public:
        explicit OcclusionQuery(std::shared_ptr<Device> device,
            uint32_t queryCount,
            std::shared_ptr<IAllocator> allocator = nullptr);
    };

    /* Pipeline statistics queries allow the application to sample
       a specified set of pipeline counters. These counters are
       accumulated by Vulkan for a set of either draw or dispatch commands
       while a pipeline statistics query is active. */

    class PipelineStatisticsQuery : public QueryPool
    {
    public:
        explicit PipelineStatisticsQuery(std::shared_ptr<Device> device,
            VkQueryPipelineStatisticFlags pipelineStatistics,
            std::shared_ptr<IAllocator> allocator = nullptr);
        VkQueryPipelineStatisticFlags getStatisticFlags() const noexcept { return pipelineStatistics; }

    private:
        VkQueryPipelineStatisticFlags pipelineStatistics;
    };

    /* Timestamps provide applications with a mechanism
       for timing the execution of commands. A timestamp
       is an integer value generated by the physical device. */

    class TimestampQuery : public QueryPool
    {
    public:
        explicit TimestampQuery(std::shared_ptr<Device> device,
            uint32_t queryCount,
            std::shared_ptr<IAllocator> allocator = nullptr);
    };

    /* The acceleration structure object may be compacted
       in order to improve performance. Before copying, an application
       must query the size of the resulting acceleration structure. */

#ifdef VK_NV_ray_tracing
    class AccelerationStructureCompactedSizeQuery : public QueryPool
    {
    public:
        explicit AccelerationStructureCompactedSizeQuery(std::shared_ptr<Device> device,
            uint32_t queryCount,
            std::shared_ptr<IAllocator> allocator = nullptr);
    };
#endif // VK_NV_ray_tracing
} // namespace magma
