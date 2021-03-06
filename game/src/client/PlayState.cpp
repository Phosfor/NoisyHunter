#include "PlayState.hpp"
#include "Root.hpp"
#include "Entity.hpp"
#include <boost/foreach.hpp>
#include <iostream>

PlayState::PlayState() {}
/*PlayState::PlayState(Engine::Root* root){
    mRoot = root;
}*/
PlayState::~PlayState() {}

void PlayState::Initialize(){
    // load resources

    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gfx"),
                                                                           "submarine1.svg", 80, 53, "submarine");

    // create GUI

    // create entities
    AddEntity(new Submarine(100,100));


    Engine::InputManager* in = Engine::Root::get_mutable_instance().GetInputMangerPtr();
    // bind keys
    Engine::KeyBindingCallback cb = boost::bind(&PlayState::OnLeaveGame, this);
    in->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
    // bind mouse
    Engine::MouseBindingCallback mcb = boost::bind(&PlayState::OnClick, this, _1);
    in->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
    in->BindMouse(mcb, Engine::BUTTON_RELEASED, sf::Mouse::Middle);
}
void PlayState::Shutdown(){
    // hm, what do we need shutdown for!?
}

void PlayState::Update(float time_delta){
    UpdateAllEntities(time_delta);

    // TODO: Networking
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->PreparePacket();
    BOOST_FOREACH(Engine::Entity& entity, mEntities){
        if (entity.GetLayer() == Engine::Entity::LAYER_REGULAR){
            Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->AddEntity(entity);
        }
    }
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket();

}



void PlayState::OnSetNoisyMode(){
    //mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode(){
    //mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}
void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position){
    //const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    //mPlayerSubmarine->SetTarget(target);
}
void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position){
    const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    Torpedo* torpedo = (Torpedo*)mPlayerSubmarine->FireTorpedoTo(target);

    AddEntity(torpedo);
}

void PlayState::OnLeaveGame() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}
void PlayState::OnClick(Engine::MouseEventArgs args){
    std::cout << "Mouse clicked at position " << args.ScreenX << "|" << args.ScreenY << std::endl;
    //OnFireTorpedo(args);
}
