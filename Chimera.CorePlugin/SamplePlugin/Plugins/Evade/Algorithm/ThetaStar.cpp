#include "ThetaStar.h"

#include "../SpellDetector/SpellDetector.h"


std::vector<EvadeGrid::Edge> get_edges(EvadeGrid& grid, const Vec3& pos, float t)
{
	  return grid.get_edges(
        pos,
        t,
        [&](const Vec3& start_pos, const Vec3& end_pos, float t)
        {
            EvadeGrid::Node node;
            if (!grid.get_nearest_node(end_pos, &node))
                return false;

            if (node.visited)
                return false;

            if ((int)(nav_mesh->get_pos_flags(end_pos) & CellFlags::Wall) != 0)
            {
                return false;
            }

            for (const auto& spell : Evade::SpellDetector::detected_spells)
            {
                if (spell->is_path_dangerous(start_pos, end_pos, local_player->get_movement_speed(), t))
                    return false;
            }

            return true;
        }
    );
}

struct HeapEntry
{
    EvadeGrid::Node* node;
    float time_to_reach;


    bool operator<(const HeapEntry& other) const
    {
        return time_to_reach > other.time_to_reach;
    }
};


std::vector<EvadeGrid::Node*> ThetaStar::run(
    EvadeGrid& grid,
    const Vec3& start_pos,
    const Vec3& end_pos,
    float movement_speed,
    float delay)
{
    EvadeGrid::Node start_pos_node;
	grid.get_nearest_node(start_pos, &start_pos_node);

    EvadeGrid::Node end_pos_node;
    grid.get_nearest_node(end_pos, &end_pos_node);

    start_pos_node.cost = delay;

    std::priority_queue<HeapEntry> heap{ };
    heap.push(HeapEntry{ &start_pos_node, start_pos.distance(end_pos) / movement_speed });

    std::unordered_map<EvadeGrid::Node*, EvadeGrid::Node*> paths{ };

    while (!heap.empty())
    {
        const auto entry = heap.top();
        const auto node = entry.node; 
        heap.pop();

        const float current_cost = node->cost;
        node->visited = true;

        if (node->center.distance(end_pos) < 1.f)
        {
            std::vector<EvadeGrid::Node*> res{ };
            res.push_back(&end_pos_node);

            EvadeGrid::Node backtrack = end_pos_node;

            while (backtrack.center.to_2d() != start_pos.to_2d())
            {
                res.push_back(paths[&backtrack]);
                backtrack = *paths[&backtrack];
            }

            return res;
        }

        for (const auto neighbor : get_edges(grid, node->center, current_cost))
        {
            draw_manager->circle(neighbor.node->center, 25.f, Color(255, 255, 255), 2.f);

            const float new_cost = current_cost + neighbor.distance / movement_speed;

            if (!neighbor.node->visited && neighbor.node->cost > new_cost)
            {
                neighbor.node->cost = new_cost;

                const float new_priority = new_cost + end_pos.distance(neighbor.node->center) / movement_speed;
                paths[neighbor.node] = node;
                heap.push({ neighbor.node, new_priority });
            }
        }
    }

    return { };
}
