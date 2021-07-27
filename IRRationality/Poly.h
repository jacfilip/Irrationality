#pragma once
#include "Object.h"
class Poly :
	public Object
{
public:
	Poly(scene::ISceneNode* node, const wchar_t* name, video::ITexture* texture, ObjectType type, GameScene* scene, HitType hitType,const vector<video::S3DVertex>& vertices);

	class PolySceneNode : public scene::ISceneNode
	{
		core::aabbox3d<f32> Box;
		vector<video::S3DVertex> Vertices;
		video::SMaterial Material;
		scene::E_PRIMITIVE_TYPE type;

	public:
		PolySceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, const vector<video::S3DVertex>& Vertices, scene::E_PRIMITIVE_TYPE type = scene::EPT_TRIANGLES)
			: ISceneNode(parent, mgr, id)
		{
			Material.Wireframe = false;
			Material.Lighting = true;
			
			this->Vertices = Vertices;
			this->type = type;

			Box.reset(Vertices[0].Pos);
			for (s32 i = 1; i < Vertices.size(); ++i)
				Box.addInternalPoint(Vertices[i].Pos);
		}

		virtual void OnRegisterSceneNode()
		{
			if (IsVisible)
				SceneManager->registerNodeForRendering(this);

			ISceneNode::OnRegisterSceneNode();
		}

		virtual void render()
		{
			//u16 indices[] = { 0,2,3, 2,1,3, 1,0,3, 2,0,1 };
			u16 indices[] = { 0,1,2,3 };
			video::IVideoDriver* driver = SceneManager->getVideoDriver();

			driver->setMaterial(Material);
			driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
			driver->drawVertexPrimitiveList(&Vertices[0], Vertices.size(), &indices[0], Vertices.size() - 2, video::EVT_STANDARD, type, video::EIT_16BIT);
		}

		virtual const core::aabbox3d<f32>& getBoundingBox() const
		{
			return Box;
		}

		virtual u32 getMaterialCount() const
		{
			return 1;
		}

		virtual video::SMaterial& getMaterial(u32 i)
		{
			return Material;
		}
	};

public:

protected:
	scene::ISceneNode* polyNode;
 	vector<video::S3DVertex> Vertices;
	
	virtual ~Poly()
	{
		polyNode->drop();
		polyNode = 0;

		Object::~Object();
	}
};

