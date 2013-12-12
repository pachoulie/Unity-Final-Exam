using UnityEngine;
using System.Collections;

public class Star : MonoBehaviour {
	
	public string SceneName;
	public bool gameFinished;
	
	// Use this for initialization
	void Start () {
		gameFinished = false;
	
	}
	
	// Update is called once per frame
	void Update () {
		if (gameFinished == true){
			if (Input.GetKey(KeyCode.KeypadEnter) || Input.GetKey ("enter"))
				Application.LoadLevel (SceneName);
		}
	}
	
	void OnTriggerEnter() {
		GameObject	clearedLevelPlane = GameObject.Find("Plane");
		clearedLevelPlane.animation.Play();
		gameFinished = true;
	}
}
