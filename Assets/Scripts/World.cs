using UnityEngine;
using System.Collections;

public class World : MonoBehaviour, ITriggered {

	public System.String animationName;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void OnTriggeredEnter () {
		Debug.Log ("World Enter !");
		//animation["test_ouverture_porte_trigger_level1"].time = 0;
		animation["world_rotation"].speed = 1;
		animation.Play("world_rotation");
	}
	
	public void OnTriggeredStay () {
		//Debug.Log ("Stay !");
	}
	
	public void OnTriggeredExit () {
		Debug.Log ("World Exit !");
		if (!animation.isPlaying)
			animation["world_rotation"].time = animation["world_rotation"].length;
		animation["world_rotation"].speed = -1;
		animation.Play("world_rotation");
	}
}
