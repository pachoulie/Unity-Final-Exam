using UnityEngine;
using System.Collections;

public class Canon : MonoBehaviour {
	
	public float minAngleLeftX;
	public float maxAngleRightX;
	public GameObject ballEmiter;
	public GameObject ball;
	public float angleX;
	
	GameObject ballToLaunch;
	GameObject nextBall;
	
	// Use this for initialization
	void Start () {
		Quaternion rot=new Quaternion();
       	rot.eulerAngles = new Vector3(0, 0, 0);
       	transform.rotation=rot;
		transform.RotateAround(transform.position, new Vector3(1, 0, 0), angleX);
		ballToLaunch = Instantiate(ball, ballEmiter.transform.position, Quaternion.identity);
		nextBall.renderer.isVisible = false;
	}
	
	// Update is called once per frame
	void Update () {
		ballToLaunch.SetActive = false;
		if (Input.GetKey(KeyCode.RightArrow)) {
			if ( angleX < maxAngleRightX ) {
				transform.RotateAround(transform.position, new Vector3(1, 0, 0), 1f);
				angleX++;
			}
		}
		if (Input.GetKey(KeyCode.LeftArrow)) {
			if ( angleX > minAngleLeftX ) {
				transform.RotateAround(transform.position, new Vector3(1, 0, 0), -1f);
				angleX--;
			}
		}
		if (Input.GetKeyDown(KeyCode.Space)) {
			nextBall = Instantiate(ball, ballEmiter.transform.position, Quaternion.identity);
			nextBall.renderer.isVisible = false;
			ballToLaunch.SetActive = true;
			ballToLaunch = nextBall;
		}
	}
}
