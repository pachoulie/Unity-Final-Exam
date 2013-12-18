using UnityEngine;
using System.Collections;

public class Star : MonoBehaviour {
	
	public string SceneName;
	bool gameFinished;

	// Use this for initialization
	void Start () {
		gameFinished = false;
	}
	
	// Update is called once per frame
	void Update () {
		GameObject	plane = GameObject.Find("Plane");

		if (gameFinished == true){
			if (Input.GetKey(KeyCode.KeypadEnter) || Input.GetKey(KeyCode.Return)) {
				if (plane && !plane.animation.isPlaying)
					plane.animation["Level_Cleard_Animation"].time =
						plane.animation["Level_Cleard_Animation"].length;
				plane.animation["Level_Cleard_Animation"].speed = -1;
				plane.animation.Play("Level_Cleard_Animation");
				Application.LoadLevel (SceneName);
			}
		} else {
			if (plane && !plane.animation.isPlaying) {
				Utility.SetAllTextActive(true);
				Debug.Log ("ON");
			} else {
				Debug.Log ("OFF");
				Utility.SetAllTextActive(false);
			}
		}
	}
	
	void OnTriggerEnter() {
		GameObject	 clearedLevelPlane = GameObject.Find("Plane");
		
		GameObject cannon = GameObject.Find("Cannon");
		
		cannon.SendMessage("setGrade");
		
		audio.Play();
		
		Debug.Log("Level finished !");
		if (clearedLevelPlane != null) {
			if (!clearedLevelPlane.animation.isPlaying)
				clearedLevelPlane.animation["Level_Cleard_Animation"].time = 0;
			clearedLevelPlane.animation["Level_Cleard_Animation"].speed = 1;
			clearedLevelPlane.animation.Play();
		}
		
		Utility.SetAllTextActive(false);
		animation.Play("Animation_Disappearing_Star");
		gameFinished = true;
	}
}
