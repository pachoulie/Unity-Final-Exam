using UnityEngine;
using System.Collections;

public class Door : MonoBehaviour, ITriggered {
	
	public string AnimationName;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void OnTriggeredEnter () {
		Debug.Log ("Enter !");
		//animation["test_ouverture_porte_trigger_level1"].time = 0;
		animation[AnimationName].speed = 1;
		animation.Play(AnimationName);
	}
	
	public void OnTriggeredStay () {
		//Debug.Log ("Stay !");
	}
	
	public void OnTriggeredExit () {
		Debug.Log ("Exit !");
		if (!animation.isPlaying)
			animation[AnimationName].time = animation[AnimationName].length;
		animation[AnimationName].speed = -1;
		animation.Play(AnimationName);
	}
}
