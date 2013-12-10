using UnityEngine;
using System.Collections;

public class Slab : MonoBehaviour {
	
	public GameObject trigger;
	
	// Use this for initialization
	void Start () {
		//trigger = (ITriggered) objectToTrigger;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter (Collider collider) {
		trigger.SendMessage("OnTriggeredEnter");
	}

	void OnTriggerExit (Collider collider) {
		trigger.SendMessage("OnTriggeredExit");
	}
	
	void OnTriggerStay (Collider collider) {
		trigger.SendMessage("OnTriggeredStay");
	}
}
