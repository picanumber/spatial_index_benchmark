#include "spatial_index_benchmark.hpp"
#include <spatialindex/SpatialIndex.h>
using namespace std;
namespace si = SpatialIndex;

int main()
{
    try
    {
        auto print_status = [](sibench::result_info const& r)
        {
            std::cout << "spatialindex: " << r;
        };

        // Generate random objects for indexing
        auto n = 100U;
        auto const boxes = sibench::generate_boxes(n);

        // Set up index
        uint32_t index_capacity = 20;
        uint32_t leaf_capacity = index_capacity;
        uint32_t dimension = 2;
        si::id_type index_id;
        std::unique_ptr<si::IStorageManager> sm(si::StorageManager::createNewMemoryStorageManager());
        std::unique_ptr<si::ISpatialIndex> rtree(si::RTree::createNewRTree(*sm, 0.7, index_capacity,
            leaf_capacity, dimension, si::RTree::RV_RSTAR, index_id));

        // Benchmark: insert
        {
            auto const marks = sibench::benchmark("insert", sibench::max_iterations, boxes,
                [&rtree] (sibench::boxes2d_t const& boxes) {

                    typedef std::array<double, 2> coord_array_t;
                    auto s = boxes.size();
                    for (decltype(s) i = 0; i < s; ++i) {
                        auto const& box = boxes[i];
                        coord_array_t p1 = { std::get<0>(box), std::get<1>(box) };
                        coord_array_t p2 = { std::get<2>(box), std::get<3>(box) };

                        si::id_type item_id(i);
                        si::Region region(
                            si::Point(p1.data(), p1.size()),
                            si::Point(p2.data(), p2.size()));
                        rtree->insertData(0, nullptr, region, item_id);
                    }
            });
            print_status(marks);
        }

        // Benchmark: query
        {
            // TODO: benchmark() should forward query parameter, not boxes
            auto const marks = sibench::benchmark("insert", sibench::max_iterations, boxes,
                [&rtree] (sibench::boxes2d_t const& boxes) {
                    ; // TODO
            });
            print_status(marks);
        }

        
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unknown error" << std::endl;
    }
    return EXIT_FAILURE;
}
