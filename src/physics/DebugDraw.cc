//
// Created by vice on 26/07/2019.
//

#include "DebugDraw.h"
#include <debug/dbg.h>
#include <game/scene.h>

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    unsigned int r, g, b, a;
    Camera* camera = scene::getCurrentScene()->getCamera();

    r = (unsigned int)(color.r * 255);
    g = (unsigned int)(color.g * 255);
    b = (unsigned int)(color.b * 255);
    a = (unsigned int)(color.a * 255);

    float min_x, min_y, max_x, max_y;
    auto bound = camera->getBound().min;
    min_x = vertices[0].x - bound.x;
    min_y = vertices[0].y - bound.y;
    max_x = vertices[2].x - bound.x;
    max_y = vertices[2].y - bound.y;
    debug::drawRect({min_x, min_y}, {max_x, max_y}, IM_COL32(r, g, b, a));
}
void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    unsigned int r, g, b, a;
    Camera* camera = scene::getCurrentScene()->getCamera();

    r = (unsigned int)(color.r * 255);
    g = (unsigned int)(color.g * 255);
    b = (unsigned int)(color.b * 255);
    a = (unsigned int)(color.a * 255);

    float min_x, min_y, max_x, max_y;
    auto bound = camera->getBound().min;
    min_x = vertices[0].x - bound.x;
    min_y = vertices[0].y - bound.y;
    max_x = vertices[2].x - bound.x;
    max_y = vertices[2].y - bound.y;
    debug::drawRectFiled({min_x, min_y}, {max_x, max_y}, IM_COL32(r, g, b, a));
}
void DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color)
{}
void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)
{}
void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{}
void DebugDraw::DrawTransform(const b2Transform &xf)
{}
void DebugDraw::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color)
{}
