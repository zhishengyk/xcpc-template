#include "geometry_base.cpp"

// 扫描线，复杂度 O(nlogn)
point_t closest_pair(vector<Point> points) {
    sort(points.begin(),points.end());
    const auto cmpy=[](const Point &a,const Point &b){if (abs(a.y-b.y)<=eps) return a.x<b.x-eps; return a.y<b.y-eps;};
    multiset<Point,decltype(cmpy)> s{cmpy};
    point_t ans=INF;
    for (size_t i=0,l=0;i<points.size();i++) {
        const point_t sqans=sqrtl(ans)+1;  // 整数情况
        // const point_t sqans=sqrtl(ans)+1;  // 浮点数情况
        while (l<i && points[i].x-points[l].x>=sqans) s.erase(s.find(points[l++]));
        for (auto it=s.lower_bound(Point{-INF,points[i].y-sqans});it!=s.end()&&it->y-points[i].y<=sqans;it++) {
            ans=min(ans,points[i].dis2(*it));
        }
        s.insert(points[i]);
    }
    return ans;
}
