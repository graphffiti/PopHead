#ifndef POPHEAD_RENDERER_RENDERER_H_
#define POPHEAD_RENDERER_RENDERER_H_

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "Renderer/layer.hpp"
#include "Renderer/layerID.hpp"
#include "Renderer/camera.hpp"

/** @defgroup Renderer Renderer
 *  Renderer module is responsible for rendering game world and managing the window.
 *
 *  Object must be add to [Renderer](@ref PopHead::Renderer::Renderer), before it's drawn. It must be added by
 *  Renderer::addObject methods.
 *
 *  Objects are stored in Layers, not directly in Renderer.
 *
 *  Renderer consists a few Layers. Each layer is drawn separately in
 *  pre-defined order. */

namespace PopHead {

/// @ingroup Renderer
namespace Renderer {

/// @ingroup Renderer
class Renderer
{
  public:
    Renderer();

    /// Destructor.
    /** Closes Window. */
    ~Renderer();
    Renderer( Renderer& ) = delete;
    Renderer& operator=( Renderer& ) = delete;

    /// Pre-defined Viewports.
    /** Viewport is a part of sf::Window, where stuff can be drawn.
     *  Usefull in split-screen applications. */
    enum Viewports
    {
        /// Viewport where its sf::Rect is equal to screen size.
        FullScreenViewport
    };

    /// Draw registered objects.
    /** Iterates through Layer s, and draw registered Object s by
     *  addObject(*) methods. */
    void draw() const;

    /// Register object to be drawn.
    /** @ingroup Renderer */
    void addObject( World::Entity::Object* const object );

    /// Register object to be drawn.
    void addObject( World::Entity::Object* const object, LayerID layerID );

    void removeObject( const World::Entity::Object* const object );
    void removeObject( std::string name, LayerID layerID );

    void removeObjects( LayerID layerID );

    auto getWindow() const -> sf::Window& { return mWindow; }
    auto getLayer( LayerID id ) -> Layer& { return mLayers[id]; }
    auto getLayer( LayerID id ) const -> const Layer& { return mLayers[id]; }

    auto getCameraPosition() const -> const sf::Vector2f& { return mCamera.getCenter(); }
    auto getCameraSize() const -> const sf::Vector2f& { return mCamera.getSize(); }

    void setCameraPosition( sf::Vector2f center ) { mCamera.setCenter( center ); }
    void setCameraSize( sf::Vector2f size ) { mCamera.setSize( size ); }
	void setCameraShakeStrength(float shakeStrength) { mCamera.setShakeStrength(shakeStrength); }

	void moveCamera( sf::Vector2f center, float speed ) { mCamera.move(center, speed); }
	void shakeCamera( float shakeStrengthLoss ) { mCamera.shake(shakeStrengthLoss); }

  private:
    Camera mCamera;
    const std::map< Viewports, sf::Rect< float > > mViewports;
    mutable sf::RenderWindow mWindow;
    mutable std::map< LayerID, Layer > mLayers;
};

}}

#endif // !POPHEAD_RENDERER_RENDERER_H_
