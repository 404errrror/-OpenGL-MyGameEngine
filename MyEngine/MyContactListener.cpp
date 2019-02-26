#include "MyContactListener.h"
#include "GameObject.h"
#include "RigidBody2D.h"


MyContactListener::MyContactListener()
{
}


MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact* contact) {

	//for (b2Contact* c = contact;;)
	//{
		GameObject* gameobjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* gameobjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (gameobjectA == nullptr || gameobjectB == nullptr)
		{
			std::cout << "MyContactListener::BeginContact   �浹�� ������Ʈ �� �ϳ� �̻��� ������Ʈ�� UserData�� ���������� ��ϵ��� �ʾҽ��ϴ�." << std::endl;
			return;
		}

		RigidBody2D* rigidbodyA = gameobjectA->transform.GetComponent<RigidBody2D>();
		RigidBody2D* rigidbodyB = gameobjectB->transform.GetComponent<RigidBody2D>();

		BoxCollider* ColliderA = gameobjectA->transform.GetComponent<BoxCollider>();
		BoxCollider* ColliderB = gameobjectB->transform.GetComponent<BoxCollider>();

		if (rigidbodyA && rigidbodyA->m_enable)
			rigidbodyA->gameObject.SetCollisionEnter(ColliderB);

		if (rigidbodyB&& rigidbodyB->m_enable)
			rigidbodyB->gameObject.SetCollisionEnter(ColliderA);

		//if (c->GetNext() != nullptr)
		//	c = c->GetNext();
		//else
		//	return;
	//}

}

void MyContactListener::EndContact(b2Contact* contact) {

	GameObject* gameobjectA = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject* gameobjectB = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (gameobjectA == nullptr || gameobjectB == nullptr)
	{
		std::cout << "MyContactListener::BeginContact   �浹�� ������Ʈ �� �ϳ� �̻��� ������Ʈ�� UserData�� ���������� ��ϵ��� �ʾҽ��ϴ�." << std::endl;
		return;
	}

	if (gameobjectA->m_remove || gameobjectA->m_remove)			// Release�� �� ȣ����� �ʵ��� �ϱ�����. ��ü�����Ҷ� ��� �ݶ��̴��� �̹� �������ִٸ� ������ ����.
		return;

	RigidBody2D* rigidbodyA = gameobjectA->transform.GetComponent<RigidBody2D>();
	RigidBody2D* rigidbodyB = gameobjectA->transform.GetComponent<RigidBody2D>();

	BoxCollider* ColliderA = gameobjectA->transform.GetComponent<BoxCollider>();
	BoxCollider* ColliderB = gameobjectB->transform.GetComponent<BoxCollider>();

	if (rigidbodyA)
		rigidbodyA->gameObject.OnCollisionExit2D(ColliderB);

	if (rigidbodyB)
		rigidbodyB->gameObject.OnCollisionExit2D(ColliderA);
}