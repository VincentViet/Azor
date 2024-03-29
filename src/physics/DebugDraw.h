//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_PHYSICS_DEBUGDRAW_H_
#define AZOR_SRC_PHYSICS_DEBUGDRAW_H_

#include <Box2D/Box2D.h>

class DebugDraw: public b2Draw
{
 public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform(const b2Transform& xf) override;
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
};

#endif //AZOR_SRC_PHYSICS_DEBUGDRAW_H_
