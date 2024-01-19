#pragma once

class EvadeGrid
{
public:
    struct Node
    {
        NavCell cell;
        Vec3 center;
        uint8_t flags;
        bool visited = false;
        float cost = 0.f;

        Node create(const Vec3& pos)
        {
            center = pos;
            cell = nav_mesh->get_nav_cell(pos);
        	flags = nav_mesh->get_cell_flags(cell);
            return *this;
        }
    };

    struct Edge
    {
        Node* node;
        float distance;
    };

    float range = 1500.f;
    float interval = 50.f;

    float iterations = floor(range / interval);
    
    std::unordered_map<int, std::unordered_map<int, Node>> nodes;
	
    EvadeGrid();
    EvadeGrid(const Vec3& start_pos);

    void draw();
    bool place(const Vec3& pos);
    bool get_nearest_coords(const Vec3& pos, int* i, int* j);
    bool get_nearest_node(const Vec3& pos, Node* node);
    Vec3 get_node_pos(int i, int j);
    std::vector<Edge> get_edges(const Vec3& pos, float t, const std::function<bool(const Vec3&, const Vec3&, float)>& is_valid);
};
