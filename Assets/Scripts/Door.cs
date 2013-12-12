using UnityEngine;
using System.Collections;

public class Door : MonoBehaviour, ITriggered {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void OnTriggeredEnter () {
		Debug.Log ("Enter !");
		//animation["test_ouverture_porte_trigger_level1"].time = 0;
		animation["door_opening"].speed = 1;
		animation.Play("door_opening");
	}
	
	public void OnTriggeredStay () {
		//Debug.Log ("Stay !");
	}
	
	public void OnTriggeredExit () {
		Debug.Log ("Exit !");
		if (!animation.isPlaying)
			animation["door_opening"].time = animation["door_opening"].length;
		animation["door_opening"].speed = -1;
		animation.Play("door_opening");
	}
}
