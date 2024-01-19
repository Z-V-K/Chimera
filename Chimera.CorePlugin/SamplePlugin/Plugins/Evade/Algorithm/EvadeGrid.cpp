#include "EvadeGrid.h"

EvadeGrid::EvadeGrid()
{
    for (uint16_t i = 0; i < nav_mesh->get_cell_count_x(); i++)
    {
        for (uint16_t j = 0; j < nav_mesh->get_cell_count_y(); j++)
        {
            NavCell cell{ i, j };
            Node node{ cell, nav_mesh->get_cell_center(cell), nav_mesh->get_cell_flags(cell) };
            nodes[i][j] = node;
        }
    }
}

EvadeGrid::EvadeGrid(const Vec3& start_pos)
{
    if (!start_pos.is_valid())
        return;

    Node n;
    nodes[0][0] = n.create(start_pos);
}

void EvadeGrid::draw()
{
    for (const auto& i : nodes)
    {
	    for (const auto& j : i.second)
	    {
            const Node* node = &j.second;
            uint8_t alpha = 30;
            Color color{ 255, 255, 255, alpha };

            if (node->flags & (uint8_t)CellFlags::Grass)
                color = { 70, 195, 45, alpha };
            else if (node->flags & (uint8_t)CellFlags::Building || node->flags & (uint8_t)CellFlags::Wall)
                color = { 180, 42, 42, alpha };
            draw_manager->circle(node->center, 25.f, color, 1, true);
	    }
    }
}

bool EvadeGrid::place(const Vec3& pos)
{
    int i, j;
    const auto found = get_nearest_coords(pos, &i, &j);

    if (!found)
        return false;

    const auto node_pos = get_node_pos(i, j);
    Node n;
    if (node_pos.distance_squared(pos) > 1)
    {
        nodes[i][j] = n.create(node_pos);
    }
    else
    {
        nodes[i][j] = n.create(pos);
    }

    return true;
}

bool EvadeGrid::get_nearest_coords(const Vec3& pos, int* i, int* j)
{
    const auto start_pos = nodes[0][0];
    if (!start_pos.center.is_valid())
        return false;

    const auto diff = pos - start_pos.center;
    const auto max_range = (iterations + .5f) * interval;

    const auto abs_x = abs(diff.x);
    const auto abs_z = abs(diff.z);

    if (abs_x < max_range && abs_z < max_range)
    {
        *i = round(diff.x / interval);
        *j = round(diff.z / interval);
        return true;
    }

    if (abs_x > abs_z)
    {
        *i = abs_x / diff.x * iterations;
        *j = round(abs_z / diff.z * abs_z / abs_x * iterations);

        return true;
    }
    else
    {
        *i = round(abs_x  / diff.x * abs_x / abs_z * iterations);
        *j = abs_z / diff.z * iterations;

        return true;
    }
}

bool EvadeGrid::get_nearest_node(const Vec3& pos, Node* node)
{
    int i, j;

    if (!get_nearest_coords(pos, &i, &j))
        return false;

    *node = nodes[i][j];
    return true;
}

Vec3 EvadeGrid::get_node_pos(int i, int j)
{
    if (!nodes[0][0].center.is_valid())
        return { };

    return nodes[0][0].center + Vec3{ (float) i, 0, (float) j } * interval;
}

std::vector<EvadeGrid::Edge> EvadeGrid::get_edges(const Vec3& pos, float t, const std::function<bool(const Vec3&, const Vec3&, float)>& is_valid)
{
    std::vector<Edge> res { };

    int i, j;
    const auto found = get_nearest_coords(pos, &i, &j);

    if (!found)
        return res;

    const auto i_min = (i == (int) - iterations) ? i : i - 1;
    const auto j_min = (j == (int) - iterations) ? j : j - 1;
    const auto i_max = (j == (int) iterations) ? i : i + 1;
    const auto j_max = (j == (int) iterations) ? j : j + 1;

    for (int x = i_min; x <= i_max; ++x)
    {
        for (int y = j_min; y <= j_max; ++y)
        {
            const Vec3 temp = get_node_pos(x, y);

            const auto insert = [&](const Vec3& pt, bool& push_back, float& distance)
            {
                if (is_valid(pos, pt, t))
                {
                    if (pt.distance(pos) > 1.f)
                    {
                        push_back = true;
                        distance = pos.distance(pt);
                    }

                    return true;
                }

                return false;
            };

            bool add_to_res = false;
            float distance = 0.f;
            if (temp.is_valid() && insert(temp, add_to_res, distance))
            {
                Node n;
                nodes[x][y] = n.create(temp);

                if (add_to_res)
					res.push_back({ &nodes[x][y], distance});
            }
            //else
            //    for idx = 1, #self.nodes[x][y] do
            //        insert(self.nodes[x][y][idx], idx == 1)
            //    end
            //end
        }
    }

    return res;
}
